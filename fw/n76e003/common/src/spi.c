#include "spi.h"

void spi_init()
{
    P10_Quasi_Mode;	// P10 (SPCLK) Quasi mode
	P00_Quasi_Mode;	// P00  (MOSI) Quasi mode
    P01_Quasi_Mode;	// P01  (MISO) Quasi mode
	set_DISMODF;	// SS General purpose I/O ( No Mode Fault ) 
    clr_SSOE;
	clr_LSBFE;	// MSB first         
    clr_CPOL;	// The SPI clock is low in idle mode
    clr_CPHA;	// The data is sample on the first edge of SPI clock 
    set_MSTR;	// SPI in Master mode 
    SPICLK_DIV2;	// Select SPI clock 
    set_SPIEN;	// Enable SPI function 
    clr_SPIF;
	set_P10;
}

uint8_t spi_write(uint8_t data)
{
    SPDR = data;
	while(!(SPSR & SET_BIT7));
	clr_SPIF;
    return SPDR;
}

uint8_t spi_read()
{
    SPDR = 0xFF;
	while(!(SPSR & SET_BIT7));
	clr_SPIF;
    return SPDR;
}