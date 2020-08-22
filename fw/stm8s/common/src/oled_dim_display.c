
#include <stdint.h>
#include <stdbool.h>
#include "oled.h"
#include "spi.h"
#include "stm8s.h"

extern uint8_t _contrast;
/*
* Fix me
*/
void oled_dim_display(bool dim)
{
    uint8_t contrast = (dim) ? 0 : _contrast;
    TRANSACTION_START
    oled_command1(SSD1306_SETCONTRAST);
    oled_command1(contrast);
    TRANSACTION_END
}