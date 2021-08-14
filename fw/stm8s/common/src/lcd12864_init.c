#include <stdint.h>
#include <stdbool.h>
#include "stm8s.h"
#include "lcd12864.h"
#include "spi.h"
#include "delay.h"

bool lcd12864_init(bool reset)
{

    /* Initialize CS pin HIGH */
    PC_DDR |= PIN4;
    PC_CR1 |= PIN4;
    PC_ODR |= PIN4;

    /* Initialize RES pin HIGH */
    PC_DDR |= PIN3;
    PC_CR1 |= PIN3;
    PC_ODR |= PIN3;

    /* Initialize DC pin LOW */
    PD_DDR |= PIN2;
    PD_CR1 |= PIN2;
    PD_ODR &= ~PIN2;

    /* Initialize spi */
    spi_init();

    if (reset)
    {
        lcd12864_command1(LCD12864_RESET); // Clear Bias: bias 0
        PC_ODR |= PIN3;
        delay_ms(2);
        PC_ODR &= ~PIN3;
        delay_ms(2);
        PC_ODR |= PIN3;
        delay_ms(10);
    }

    //lcd12864_command1(0xA1); // Reverse direction (SEG131-SEG0)
    //lcd12864_command1(0xC8); // SHL 1,COM63-COM0
    lcd12864_command1(0xA2); // Clear Bias: bias 0

    // Power_Control 4 (internal converter ON) + 2 (internal regulator ON) + 1 (internal follower ON)
    lcd12864_command1(0x28 | 0x07); // Power Control

    /*  Regulator resistor select
    **            1+Rb/Ra  Vo=(1+Rb/Ra)Vev    Vev=(1-(63-a)/162)Vref   2.1v
    **            0  3.0       4  5.0(default)
    **            1  3.5       5  5.5
    **            2  4         6  6
    **            3  4.5       7  6.4
    */
    lcd12864_command1(0x20 | 0x05); // Regulator resistor

    // a(0-63) 32=default   Vev=(1-(63-a)/162)Vref   2.1v
    lcd12864_command1(0x81); // Set Contrast
    lcd12864_command1(21);
    lcd12864_command1(0x40); // DisplayLine=0
    lcd12864_clear(0x00);
    lcd12864_command1(0xAF); // Display ON
    return true;
}