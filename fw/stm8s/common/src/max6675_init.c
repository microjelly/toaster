#include "max6675.h"
#include "delay.h"
#include "stm8s.h"
//#include "spi.h"


void max6675_init()
{
    // CS (PA1) as output
    PA_DDR |= PIN1;
    PA_CR1 |= PIN1;
    PA_ODR |= PIN1; // CS high

    // CLK PC5 as output
    PC_DDR |= PIN5;
    PC_CR1 |= PIN5;
    PC_ODR |= PIN5; // CLK high

    delay_ms(600); // gross startup delay
}