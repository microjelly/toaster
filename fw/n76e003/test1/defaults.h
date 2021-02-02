#ifndef DEFAULTS_H
#define DEFAULTS_H

#define LED0 P14
#define SW0 P13

#define BUZZER_CLK (16000000 / 12)
#define BUZZER_FREQ (1200 * 2)
#define BUZZER_PERIOD (0xFFFF - ((BUZZER_CLK / BUZZER_FREQ) - 1))

#define PWM_CLK (16000000 / 8)
#define PWM_FREQ 240
#define PWM_PERIOD ((PWM_CLK / PWM_FREQ) - 1)
#define PWM_SLICE (PWM_PERIOD / 100)

#define SRV0_START 0

#endif /* DEFAULTS_H */