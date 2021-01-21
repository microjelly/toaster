#include <stdint.h>
#include "delay.h"
#include "max31855k.h"
#include "stm8s.h"

uint16_t max31855k_read()
{
    volatile uint16_t value = 0;
    // I'm doing bit-bang spi here to return a 16bit uint... 
    // there is probably a cleaner way..
    MAX31855K_TRANSACTION_START
    for (uint8_t i = 16; i >= 1; --i)
    {
        PC_ODR &= ~PIN5;
        delay_us(100);
        if (PC_IDR & PIN7)
            value |= (1 << (i - 1));

        PC_ODR |= PIN5;
    }
    // I stop after 16bits, it works... 
    MAX31855K_TRANSACTION_END
    // With just 16 bits.. We only get a working or not working...
    if (value & 0x01)
    {
        return 0;
    }
    // Ignoring +/- (always returns as postivive)
    return ( value & 0x7fff ) >> 2;
}