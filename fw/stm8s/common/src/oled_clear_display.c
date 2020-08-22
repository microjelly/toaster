
#include <stdint.h>
#include "oled.h"
#include "spi.h"
#include "stm8s.h"

void oled_clear_display(void)
{
    TRANSACTION_START
    for (uint8_t page = 0; page < (OLED_LCDHEIGHT / 8); page++)
    {
        OLED_MODE_COMMAND
        uint8_t dlist1[] = {
            0xB0 + page,
            OLED_PIX_START,
            0x10};
        oled_command_list(dlist1, sizeof(dlist1));
        OLED_MODE_DATA
        for (uint16_t i = 0; i < OLED_LCDWIDTH; i++)
            spi_write(0x00);
    }
    TRANSACTION_END
}
