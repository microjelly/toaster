#ifndef BEEP_H
#define BEEP_H

/*
* BEEP -> PD4
*/

#include <stdint.h>
#include "stm8s.h"

void beep_init(void);
void beep_on(void);
void beep_off(void);
void beep_freq(uint8_t freq);

#endif /* BEEP_H */