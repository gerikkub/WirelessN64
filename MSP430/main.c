#include <msp430.h> 
#include "nrf24l01.h"
#include "spi.h"

/*
 * main.c
 */

#define N64_DATA(x)	(*(unsigned char*)(0x276 + (x)))

unsigned char config;

void _delay_ms(int time) {
	while(time--)
	{
		__delay_cycles(16000);
	}
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    DCOCTL = CALDCO_16MHZ;
    BCSCTL1 = CALBC1_16MHZ;
    BCSCTL1 &= ~(DIVA0|DIVA1);
    BCSCTL2 |= DIVS_3;

    BCSCTL2 = 0;

    P1DIR |= BIT0;

    unsigned char data[4] = {0xDE, 0xAD, 0xBE, 0xEF};
      initNrf24l01();

      configNrf24l01(1, 4);

      //unsigned char num[4] = {0xAA, 0xCD, 0xEF, 0x56};

      flushTX();

      /*while(1) {

    	 writeSTATUS(0x70);

         sendData(num, 4);
         //sendData((unsigned char*)&num[0], 4);
         //P1OUT ^= BIT0;

         //_delay_ms(2500.);
         _delay_cycles(165);
         num[0]++;
      }*/

    while(1) {

    	tryCommand();

    	data[0] = N64_DATA(0);
    	data[1] = N64_DATA(1);
    	data[2] = N64_DATA(2);
    	data[3] = N64_DATA(3);

    	writeSTATUS(0x70);
    	sendData(data, 4);

        _delay_ms(16.);
    }

	return 0;
}
