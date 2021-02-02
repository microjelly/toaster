#ifndef CLOCK_H
#define CLOCK_H

#ifndef F_CPU
#warning "F_CPU not defined, using 2MHz by default"
#define F_CPU 16000000UL
#endif

#include <stdint.h>
#include "stm8s.h"

inline void clock_init(void)
{
#if (F_CPU == 2000000UL)

#elif (F_CPU == 16000000UL)
    CLK_CKDIVR = 0x00; // Set the frequency to 16 MHz
#endif
}

#endif /* CLOCK_H */