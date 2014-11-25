#include <avr/io.h>
#include <avr/interrupt.h>

#include "nrf24l01.h"
#include "usart.h"

unsigned char readConsoleData();

volatile int n64BitsRead;
volatile unsigned char n64Data;
volatile char newData;
unsigned char *n64DataStart;

int main(){
  
   DDRB = 0;
   DDRD = 0x07;
   DIDR0 = 0;
   char highByte;
 
   n64BitsRead = 0;
   newData = 0;

   initUSART();
   initNrf24l01();

   printAllReg();

   configNrf24l01(1, 4);

   n64DataStart = (unsigned char*)&n64Data;
   unsigned char data[4] = {0,0,0,0};

   powerRxUp();
   
   while(1) {
      PORTB &= ~(1 << 1);

      n64Data = readConsoleData();
      sendFourBytes(data[0],data[1],data[2],data[3]);

      printHex8(n64Data);

      initNrf24l01Pins();

      if(dataReady()) {
         readRX_PAYLOAD(0, data, 16);
         printHex8(data[0]);
      }
      printEndl();
         
   }
}
