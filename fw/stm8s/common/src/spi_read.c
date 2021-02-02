#include "spi.h"
#include "stm8s.h"

uint8_t spi_read()
{
    spi_write(0xFF);
    while (!(SPI_SR & SPI_SR_RxNE))
        ;
    return SPI_DR;
}