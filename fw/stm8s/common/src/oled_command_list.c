
#include <stdint.h>
#include "oled.h"
#include "spi.h"
#include "stm8s.h"

void oled_command_list(const uint8_t *c, uint8_t n)
{
    OLED_MODE_COMMAND
    for (uint8_t i = 0; i < n; i++)
        spi_write(c[i]);
}