#include <msp430.h>
#include "nrf24l01.h"
#include "spi.h"

#define SPI_SS PD7

static int PTX;

void _delay_us(int time) {
	while(time--)
	{
		__delay_cycles(16);
	}
}

void initSPI() {
    spi_init();
}

void ssLow() {
	P1OUT &= ~BIT5;
}

void ssHigh() {
   P1OUT |= BIT5;
}

void ceLow() {
   P1OUT &= ~BIT3;
}

void ceHigh() {
   P1OUT |= BIT3;
}

void initNrf24l01() {
   P1DIR |= BIT3;

   initSPI();

   ssHigh();
   ceLow();
}

unsigned char sendByte(unsigned char data) {
	return spi_transfer(data);
}
void readRegister(char addr, unsigned char *data, int bytes) {

   ssLow();

   sendByte(addr & 0x1F);

   while(bytes) {
     *data = sendByte(0);
      data++;
      bytes--;
   }

   ssHigh();
}

void writeRegister(char addr, unsigned char *data, int bytes) {

   ssLow();

   sendByte((addr & 0x1F) | 0x20);

   while(bytes--) {
      sendByte(*data);
      data++;
   }

   ssHigh();
}

unsigned char readCONFIG() {
   unsigned char data;

   readRegister(0, &data, 1);

   return data;
}

unsigned char readEN_AA() {
   unsigned char data;
   readRegister(1, &data, 1);
   return data;
}

unsigned char readEN_RXADDR() {
   unsigned char data;
   readRegister(2, &data, 1);
   return data;
}

unsigned char readSETUP_AW() {
   unsigned char data;
   readRegister(3, &data, 1);
   return data;
}

unsigned char readSETUP_RETR() {
   unsigned char data;
   readRegister(4, &data, 1);
   return data;
}

unsigned char readRF_CH() {
   unsigned char data;
   readRegister(5, &data, 1);
   return data;
}

unsigned char readRF_SETUP() {
   unsigned char data;
   readRegister(6, &data, 1);
   return data;
}

unsigned char readSTATUS() {
   unsigned char data;
   readRegister(7, &data, 1);
   return data;
}

unsigned char readOBSERVE_TX() {
   unsigned char data;
   readRegister(8, &data, 1);
   return data;
}

unsigned char readCD() {
   unsigned char data;
   readRegister(9, &data, 1);
   return data;
}

void readRX_ADDR_P(int a, unsigned char *data) {
   if (a < 2) {
      readRegister(0xA + a, data, 5);
   } else {
      readRegister(0xA + a, data, 1);
   }
}

void readTX_ADDR(unsigned char *data) {
   readRegister(0x10, data, 5);
}

unsigned char readRX_PW_P(int a) {
   unsigned char data;
   readRegister(0x11 + a, &data, 1);
   return data;
}

unsigned char readFIFO_STATUS(){
   unsigned char data;
   readRegister(0x17, &data, 1);
   return data;
}

void writeCONFIG(unsigned char data){
   writeRegister(0, &data, 1);
   PTX = ~(data & 1);
}

void writeEN_AA(unsigned char data){
   writeRegister(1, &data, 1);
}

void writeEN_RXADDR(unsigned char data){
   writeRegister(2, &data, 1);
}

void writeSETUP_AW(unsigned char data){
   writeRegister(3, &data, 1);
}

void writeSETUP_RETR(unsigned char data){
   writeRegister(4, &data, 1);
}

void writeRF_CH(unsigned char data){
   writeRegister(5, &data, 1);
}

void writeRF_SETUP(unsigned char data){
   writeRegister(6, &data, 1);
}

void writeSTATUS(unsigned char data){
   writeRegister(7, &data, 1);
}

void writeRX_ADDR_P(int a, unsigned char *data) {
   writeRegister(0xA + a, data, a < 2 ? 5 : 1);
}

void writeTX_ADDR(unsigned char *data) {
   writeRegister(0x10, data, 5);
}

void writeRX_PW_P(int a, unsigned char data) {
   writeRegister(0x11 + a, &data, 1);
}

void writeFIFO_STATUS(unsigned char data) {
   writeRegister(0x17, &data, 1);
}

void writeTX_PAYLOAD(unsigned char *data, int bytes) {

   ssLow();

   sendByte(0xA0);

   while(bytes--) {
      sendByte(*data);
      data++;
   }

   ssHigh();
}

void flushTX() {
   ssLow();

   sendByte(0xE1);

   ssHigh();
}

void flushRX() {
   ssLow();

   sendByte(0xE2);

   ssHigh();
}

int isSending() {
   if(PTX) {
      unsigned char status = readSTATUS();

      return status & ((1 << TX_DS) | (1 << MAX_RT));
   }
   return 0;
}

int dataReady() {
   unsigned char status = readSTATUS();

   return status & (1 << RX_DR);

   /*if(status & (1 << RX_DR)) {
      return 1;
   }*/
   return (readFIFO_STATUS() & (1 << RX_EMPTY));
}

void readRX_PAYLOAD(int a, unsigned char *data, int size) {

   ssLow();

   sendByte(0x61);

   while(size--) {
      *data = sendByte(0);
      data++;
   }

   ssHigh();

   writeSTATUS(1 << RX_DR);
}

void configNrf24l01(unsigned char channel, unsigned char payloadSize) {
   if(channel < 83) {
      writeRF_CH(channel);
   }

   writeRX_PW_P(0, payloadSize);
   writeRX_PW_P(1, payloadSize);
}

void powerRxUp() {
   PTX = 0;
   ceLow();
   writeCONFIG((1 << EN_CRC)|(1 << PWR_UP)|(1 << PRIM_RX));
   ceHigh();
   writeSTATUS((1 << TX_DS)|(1 << MAX_RT));
   flushRX();
}

void powerTxUp() {
   PTX = 1;
   writeCONFIG((1 << EN_CRC)|(1 << PWR_UP));
}

void sendData(unsigned char *data, int bytes) {
   //while(PTX && !(readFIFO_STATUS() & TX_EMPTY));

   ceLow();

   __delay_cycles(800000);

   powerTxUp();
   flushTX();
   //printAllReg();
   writeTX_PAYLOAD(data, bytes);

   ceHigh();

   /*__delay_cycles(200);

   ceLow();*/
}

char volatile readReg;

void printAllReg() {

   readReg = readCONFIG();
   readReg = readEN_AA();
   readReg = readEN_RXADDR();
   readReg = readSETUP_AW();
   readReg = readSETUP_RETR();
   readReg = readRF_CH();
   readReg = readRF_SETUP();
   readReg = readSTATUS();
   readReg = readOBSERVE_TX();
   readReg = readCD();
   readReg = readFIFO_STATUS();
}
