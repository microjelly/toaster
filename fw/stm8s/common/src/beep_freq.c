#include "beep.h"

void beep_freq(uint8_t freq)
{
    BEEP_CSR_DIV(freq);
}