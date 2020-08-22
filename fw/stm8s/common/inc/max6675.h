#ifndef MAX6675_H
#define MAX6675_H

#include <stdint.h>

/**
 * Initialize MAX6675.
 *
 * Pinout:
 *  CS   -> PA1
 *  SCK  -> PC5 [spi]
 *  MISO -> PC7 [spi]
 *
 */

#define MAX6675_TRANSACTION_START \
    PC_ODR |= PIN5;               \
    PA_ODR &= ~PIN1;
#define MAX6675_TRANSACTION_END \
    PA_ODR |= PIN1;

void max6675_init();

uint16_t max6675_read();

#endif /* MAX6675_H */
