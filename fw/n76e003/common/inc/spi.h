#ifndef SPI_H
#define SPI_H

#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"

/*
 * Initialize SPI
 *
 * Pinout:
 * SCK  -> P1.0
 * MOSI -> P0.0
 * MISO -> P0.1
 * CS   -> user defined
 */
void spi_init();

uint8_t spi_write(uint8_t data);

uint8_t spi_read();

#endif /* SPI_H */