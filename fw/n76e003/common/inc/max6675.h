#ifndef MAX6675_H
#define MAX6675_H

#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "spi.h"

/**
 * Initialize MAX6675.
 *
 * Pinout:
 *  CS   -> P3.0
 *  SCK  -> P1.0 [spi]
 *  MISO -> P0.1 [spi]
 *
 */

#define MAX6675_TRANSACTION_START \
    set_P10;               \
    clr_P30;
#define MAX6675_TRANSACTION_END \
    set_P10;               \
    set_P30;

void max6675_init();

uint16_t max6675_read();

#endif /* MAX6675_H */
