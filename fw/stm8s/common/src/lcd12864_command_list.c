#include <stdint.h>
#include "lcd12864.h"
#include "spi.h"
#include "stm8s.h"

void lcd12864_command_list(const uint8_t *c, uint8_t n)
{
    LCD12864_TRANSACTION_START
    LCD12864_MODE_COMMAND
    for (uint8_t i = 0; i < n; i++)
        spi_write(c[i]);
    LCD12864_TRANSACTION_END
}