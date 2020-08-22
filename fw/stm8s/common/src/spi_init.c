#include "spi.h"
#include "stm8s.h"

void spi_init()
{
    /* Initialize SPI master at 2mHz  */
    //SPI_CR2 = SPI_CR2_SSM | SPI_CR2_SSI;
    SPI_CR1 = SPI_CR1_MSTR; // | SPI_CR1_BR(0b010);
}