
#include <stdbool.h>
#include "lcd12864.h"
#include "spi.h"
#include "stm8s.h"

void lcd12864_clear_display(bool i)
{
    lcd12864_command1(i ? LCD12864_CLEARON : LCD12864_CLEAROFF);
}