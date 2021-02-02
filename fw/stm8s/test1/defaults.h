#ifndef DEFAULTS_H
#define DEFAULTS_H

#define LED0_PORT PB
#define LED0_PIN PIN5

#define SSR0_PORT PD
#define SSR0_PIN PIN3
#define SSR1_PORT PA
#define SSR1_PIN PIN3

#define PWM_PSCR 2
#define PWM_CLK (F_CPU / 4)
#define PWM_FREQ 240
#define PWM_ARR (PWM_CLK / PWM_FREQ) - 1

#endif /* DEFAULTS_H */