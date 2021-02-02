#include "spi.h"
#include "stm8s.h"

void spi_write(uint8_t data)
{
    SPI_DR = data;
    while (!(SPI_SR & SPI_SR_TXE))
        ;
}