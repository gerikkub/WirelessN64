/*
 * spi.h
 *
 *  Created on: Sep 24, 2014
 *      Author: Gerik
 */

#ifndef SPI_H_
#define SPI_H_

typedef unsigned char uint8_t;
typedef unsigned int  uint16_t;

void spi_init();
uint8_t spi_transfer(uint8_t);  // SPI xfer 1 byte
uint16_t spi_transfer16(uint16_t);  // SPI xfer 2 bytes

#endif /* SPI_H_ */
