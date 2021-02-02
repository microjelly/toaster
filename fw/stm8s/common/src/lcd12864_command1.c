#include <stdint.h>
#include "lcd12864.h"
#include "spi.h"

void lcd12864_command1(uint8_t c)
{
    LCD12864_TRANSACTION_START
    LCD12864_MODE_COMMAND
    spi_write(c);
    LCD12864_TRANSACTION_END
}
