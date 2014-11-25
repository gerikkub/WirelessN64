/*
 * spi.c
 *
 *  Created on: Sep 24, 2014
 *      Author: Gerik
 */



#include <msp430.h>
#include "spi.h"

/* USCI 16-bit transfer functions rely on the Little-Endian architecture and use
 * an internal uint8_t * pointer to manipulate the individual 8-bit segments of a
 * 16-bit integer.
 */

// USCI for F2xxx and G2xx3 devices


void spi_init()
{
	/* Configure ports on MSP430 device for USCI_A */
	P1SEL |= BIT1 | BIT2 | BIT4;
	P1SEL2 |= BIT1 | BIT2 | BIT4;

	P1OUT |= BIT5;
	P1DIR |= BIT5;

	/* USCI-A specific SPI setup */
	UCA0CTL1 |= UCSWRST;
	UCA0MCTL = 0x00;  // Clearing modulation control per TI user's guide recommendation
	UCA0CTL0 = UCCKPH | UCMSB | UCMST | UCMODE_0 | UCSYNC;  // SPI mode 0, master
	UCA0BR0 = 0x10;  // SPI clocked at same speed as SMCLK
	UCA0BR1 = 0x00;
	UCA0CTL1 = UCSSEL_2;  // Clock = SMCLK, clear UCSWRST and enables USCI_A module.
}

uint8_t spi_transfer(uint8_t inb)
{
	UCA0TXBUF = inb;
	while ( !(IFG2 & UCA0RXIFG) )  // Wait for RXIFG indicating remote byte received via SOMI
		;
	return UCA0RXBUF;
}

uint16_t spi_transfer16(uint16_t inw)
{
	unsigned int retw;
	unsigned char *retw8 = (uint8_t *)&retw, *inw8 = (uint8_t *)&inw;

	UCA0TXBUF = inw8[1];
	while ( !(IFG2 & UCA0RXIFG) )
		;
	retw8[1] = UCA0RXBUF;
	UCA0TXBUF = inw8[0];
	while ( !(IFG2 & UCA0RXIFG) )
		;
	retw8[0] = UCA0RXBUF;
	return retw;
}
