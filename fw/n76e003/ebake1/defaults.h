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

#define NUMBER_OF_OUTPUTS 2

#define DEFAULT_TEMP_COOL 45
#define DEFAULT_TEMP_HOT 50
#define DEFAULT_MAX_TEMP 280
#define DEFAULT_MAX_DEVIATION 20

enum
{
    SM_GO_NULL = 0,
    SM_NULL,
    SM_GO_RUN,
    SM_RUN,
    SM_START_COOLING,
    SM_COOLING,
    SM_DONE,
    SM_DONE_Q
};

enum
{
    DISPLAY_CURRENT_SECOND = 0,
    DISPLAY_COUNTDOWN_TIMER,
    DISPLAY_PROFILE_TIMER,
};

enum
{
    ELEMENT_TOP = 0,
    ELEMENT_BOTTOM
};

enum
{
    PROFILE_FIRST = 0,
    PROFILE_MIDDLE,
    PROFILE_LAST,
};

#define PID_P 2
#define PID_I 3
#define PID_D 0

#define BIAS_MAX 100
#define BIAS_B 100
#define BIAS_T 75

const uint8_t profile[3][2] = {{150,40},{190,10},{245,12}};
#define PROFILE_LEN 3
#define PROFILE_TEMP 0
#define PROFILE_TIME 1
#define PROFILE_OVERSHOOT 10 // FIX the PID, don't do this!!
#define PROFILE_ADJUST 1

#endif /* DEFAULTS_H */