
#include <stdbool.h>
#include "oled.h"
#include "spi.h"
#include "stm8s.h"

void oled_invert_display(bool i)
{
    TRANSACTION_START
    oled_command1(i ? SSD1306_INVERTDISPLAY : SSD1306_NORMALDISPLAY);
    TRANSACTION_END
}