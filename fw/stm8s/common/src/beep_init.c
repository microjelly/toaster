#include "beep.h"

void beep_init(void)
{
    BEEP_CSR &= ~BEEP_CSR_BEEPDIV; /* Clear bits */
    BEEP_CSR |= BEEP_CALIBRATION_DEFAULT;
}