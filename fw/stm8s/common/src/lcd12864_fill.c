#include <stdint.h>
#include "lcd12864.h"
#include "spi.h"

void lcd12864_clear(uint8_t d)
{
    for (uint8_t page = 0; page < 8; page++)
    {
        uint8_t dlist1[] = {
            0x40 | LCD12864_PIX_START,
            0xB0 | page,
            (0x10 | (0 >> 4)),
            (0x0f & 0) | 0x04};
        lcd12864_command_list(dlist1, sizeof(dlist1));
        LCD12864_TRANSACTION_START
        LCD12864_MODE_DATA
        for (uint8_t idx = 0; idx < 128; idx++)
            spi_write(d);
        LCD12864_TRANSACTION_END
    }
}
