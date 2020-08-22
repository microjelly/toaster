#include "beep.h"

void beep_off(void)
{
    BEEP_CSR &= ~BEEP_CSR_EN;
}