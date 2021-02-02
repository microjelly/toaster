#include "max6675.h"

void max6675_init()
{
    /* Initialize CS pin HIGH */
    P30_PushPull_Mode;
	set_P30;

    /* Initialize spi */
    spi_init();
}

uint16_t max6675_read()
{
    MAX6675_TRANSACTION_START
    uint8_t val0 = spi_read();
	uint8_t val1 = spi_read();
    MAX6675_TRANSACTION_END

    uint16_t value = MAKEWORD(val0, val1);
    if (value & 0x4)
    {
        return 0;
    }
    return (value >> 3);
}