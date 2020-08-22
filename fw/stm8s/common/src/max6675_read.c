#include <stdint.h>
#include "delay.h"
#include "max6675.h"
#include "stm8s.h"

uint16_t max6675_read()
{
    volatile uint16_t value = 0;
    MAX6675_TRANSACTION_START
    for (uint8_t i = 16; i >= 1; --i)
    {
        PC_ODR &= ~PIN5;
        delay_us(100);
        if (PC_IDR & PIN7)
            value |= (1 << (i - 1));

        PC_ODR |= PIN5;
    }
    MAX6675_TRANSACTION_END
    if (value & 0x4)
    {
        return 0;
    }
    return (value >> 3);
}