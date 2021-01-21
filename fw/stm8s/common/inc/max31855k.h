#ifndef MAX31855K_H
#define MAX31855K_H

#include <stdint.h>

/**
 * Initialize MAX31855K.
 *
 * Pinout:
 *  CS   -> PA1
 *  SCK  -> PC5 [spi]
 *  MISO -> PC7 [spi]
 *
 */

#define MAX31855K_TRANSACTION_START \
    PC_ODR |= PIN5;               \
    PA_ODR &= ~PIN1;
#define MAX31855K_TRANSACTION_END \
    PA_ODR |= PIN1;

void max31855k_init();

uint16_t max31855k_read();

#endif /* MAX31855K_H */
