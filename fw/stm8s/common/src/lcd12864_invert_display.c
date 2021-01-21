#include <stdbool.h>
#include "lcd12864.h"
#include "spi.h"
#include "stm8s.h"

void lcd12864_invert_display(bool i)
{
    lcd12864_command1(i ? LCD12864_INVERTDISPLAY : LCD12864_NORMALDISPLAY);
}