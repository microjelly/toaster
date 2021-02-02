#include "beep.h"

void beep_on(void)
{
    BEEP_CSR |= BEEP_CSR_EN;
}