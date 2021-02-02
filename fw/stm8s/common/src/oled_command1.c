#include <stdint.h>
#include "oled.h"
#include "spi.h"

void oled_command1(uint8_t c)
{
    OLED_MODE_COMMAND
    spi_write(c);
}
