#ifndef _NRF24L01_H_
#define _NRF24L01_H_

#define MASK_RX_DR   6
#define MASK_TX_DS   5
#define MASK_MAX_RF  4
#define EN_CRC       3
#define CRCO         2
#define PWR_UP       1
#define PRIM_RX      0

#define  ENAA_P5  5
#define  ENAA_P4  4
#define  ENAA_P3  3
#define  ENAA_P2  2
#define  ENAA_P1  1
#define  ENAA_P0  0

#define ERX_P5    5
#define ERX_P4    4
#define ERX_P3    3
#define ERX_P2    2
#define ERX_P1    1
#define ERX_P0    0

#define AW1 1
#define AW0 0

#define ARD3   7
#define ARD2   6
#define ARD1   5
#define ARD0   4
#define ARC3   3
#define ARC2   2
#define ARC1   1
#define ARC0   0

#define CONT_WAVE    7
#define RF_DR_LOW    6
#define PLL_LOCK     4
#define RF_DR_HIGH   3
#define RF_PWR1      2
#define RF_PWR0      1

#define RX_DR     6
#define TX_DS     5
#define MAX_RT    4
#define RX_P_NO2  3
#define RX_P_NO1  2
#define RX_P_NO0  1
#define STATUS_TX_FULL   0

#define RPD 0

#define TX_REUSE  6
#define FIFO_TX_FULL   5
#define TX_EMPTY  4
#define RX_FULL   1
#define RX_EMPTY  0



void initNrf24l01();
void ssLow();
void ssHigh();
void ceLow();
void ceHigh();

unsigned char readCONFIG();
unsigned char readEN_AA();
unsigned char readEN_RXADDR();
unsigned char readSETUP_AW();
unsigned char readSETUP_RETR();
unsigned char readRF_CH();
unsigned char readRF_SETUP();
unsigned char readSTATUS();
unsigned char readOBSERVE_TX();
unsigned char readCD();
void readRX_ADDR_P(int a, unsigned char *data);
void readTX_ADDR(unsigned char *data);
unsigned char readRX_PW_P(int a);
unsigned char readFIFO_STATUS();

void writeCONFIG(unsigned char data);
void writeEN_AA(unsigned char data);
void writeEN_RXADDR(unsigned char data);
void writeSETUP_AW(unsigned char data);
void writeSETUP_RETR(unsigned char data);
void writeRF_CH(unsigned char data);
void writeRF_SETUP(unsigned char data);
void writeSTATUS(unsigned char data);
void writeRX_ADDR_P(int a, unsigned char *data);
void writeTX_ADDR(unsigned char *data);
void writeRX_PW_P(int a, unsigned char data);
void writeFIFO_STATUS(unsigned char data);

void writeTX_PAYLOAD(unsigned char *data, int size);
void readRX_PAYLOAD(int a, unsigned char *data, int size);

void flushTX();
void flushRX();
int isSending();
int dataReady();

void configNrf24l01(unsigned char channel, unsigned char payloadSize);
void powerRxUp();
void powerTxUp();

void sendData(unsigned char *data, int bytes);

void printAllReg();

#endif
