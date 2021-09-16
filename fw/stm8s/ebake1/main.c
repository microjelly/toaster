/*
 * STM8S-TOASTER
 *
 * LED
 *  LED0 -> [11] PB5 (RED; HOT)
 * SSR
 *  SSR0 -> [20] PD3 [tim2-ch2] > TOP
 *  SSR1 -> [10] PA3 [tim2-ch3] > BOTTOM
* SERVO
 *  SRV0 -> [13] ??
 * SW
 *  SW0  -> [12] PB4
 * OLED
 *  CS   -> [14] PC4
 *  DC   -> [19] PD2
 *  RES  -> [06] PA2
 *  SCK  -> [15] PC5 [spi]
 *  MOSI -> [16] PC6 [spi]
 * MAX6675
 *  CS   -> [05] PA1
 *  SCK  -> [15] PC5 [spi]
 *  MISO -> [17] PC7 [spi]
 * BEEP
 *  BEEP -> [01] PD4
 * UART1    115200 8N1
 *  TX   -> [02] PD5
 *  RX   -> [03] PD6
 */

#include <stdint.h>
#include <stdbool.h>
#include <stm8s.h>
#include <clock.h>
#include <format.h>
#include <uart_stdout.h>
#include <uart.h>
#include <lcd12864.h>
#include <max6675.h>
#include <beep.h>

#include "defaults.h"
#include "strings.h"
#include "pid.h"

void setOutput(uint8_t value0, uint8_t value1)
{
    uint16_t ccr = ((PWM_CLK / PWM_FREQ) * value0) / 100;
    if (ccr > 0)
    {
        TIM2_CCR2H = ccr >> 8; // Start off
        TIM2_CCR2L = ccr & 0x00FF;
    }
    else
    {
        TIM2_CCR2H = 0;
        TIM2_CCR2L = 0;
    }
    ccr = ((PWM_CLK / PWM_FREQ) * value1) / 100;
    if (ccr > 0)
    {
        TIM2_CCR3H = ccr >> 8; // Start off
        TIM2_CCR3L = ccr & 0x00FF;
    }
    else
    {
        TIM2_CCR3H = 0;
        TIM2_CCR3L = 0;
    }
}

void setText(bool stdout, bool isTitle, struct LCD12864_SEGMENT *segment, uint8_t *format, ...)
{
    uint8_t *ptr = segment->buffer;
    lcd12864_clear_segment(segment);

    if (isTitle)
    {
        *ptr++;
        *ptr++;
    }

    va_list args;
    va_start(args, format);
    format_vsprintf(ptr, format, args);
    va_end(args);

    if (stdout)
    {
        if (isTitle)
            *ptr++;
        putstring((isTitle) ? "TITLE: '" : "STATUS: '");
        putstring(ptr);
        putstring("'\r\n");
    }
}

/* TIM1 Update/Overflow interrupt handling routine */
static volatile uint16_t tim1Value;
void TIM1_update(void) __interrupt(TIM1_OVR_UIF_IRQ)
{
    tim1Value++;
    TIM1_SR1 &= ~TIM_SR1_UIF;
}

static volatile uint8_t extiButton;
ISR(gpio_isr, EXTI_PORTB_vector)
{
    extiButton++;
}

int main(void)
{
    volatile uint16_t previousTicks = 0xffff;
    volatile uint16_t previousSecond = 0xffff;
    volatile uint8_t previousDutyCycle[NUMBER_OF_OUTPUTS] = {0, 0};
    volatile uint8_t currentDutyCycle[NUMBER_OF_OUTPUTS] = {0, 0};

    volatile bool isHeating = false;
    volatile uint8_t stateMachine = SM_GO_NULL;
    volatile uint8_t beeps = 2;
    volatile bool beepOn = false;

    volatile uint16_t profileTimer = 0;
    volatile bool profileTimerRunning = false;
    volatile uint8_t profileStep = 0;
    volatile uint16_t desiredTemperature = 0;

    volatile uint8_t currentPidDutyCycle = 0;
    volatile uint8_t previousPidDutyCycle = 0xff;

    volatile uint16_t countdownTimer = 0;
    volatile uint8_t displayTime = DISPLAY_CURRENT_SECOND;
    volatile uint8_t displayType = '+';

    volatile pid_struct pid = {
        0, 0,   //dstate, istate
        10, 0,  //imax, imin
        99, 0,  //max/min output limits
        PID_P, PID_I, PID_D //p, i, d gains
    };

    /* LED setup */
    PORT(LED0_PORT, DDR) |= LED0_PIN;
    PORT(LED0_PORT, CR1) |= LED0_PIN;
    PORT(LED0_PORT, ODR) |= LED0_PIN;

    sim();
    clock_init();

    /* TIM1 setup ~250ms */
    tim1Value = 0;
    TIM1_PSCRH = 0x10;
    TIM1_PSCRL = 0x00;
    TIM1_ARRH = 0x03;
    TIM1_ARRL = 0xd0;
    TIM1_IER |= TIM_IER_UIE;
    TIM1_CR1 |= TIM_CR1_CEN;

    /* TIM2/PWM setup */
    TIM2_PSCR = PWM_PSCR;
    TIM2_ARRH = PWM_ARR >> 8;
    TIM2_ARRL = PWM_ARR & 0x00FF;
    PORT(SSR0_PORT, DDR) |= SSR0_PIN;
    PORT(SSR0_PORT, CR1) |= SSR0_PIN;
    TIM2_CCER1 |= TIM2_CCER1_CC2E;
    TIM2_CCMR2 |= (TIM2_CCMR2_OC2M1 | TIM2_CCMR2_OC2M2);
    TIM2_CCMR2 &= ~TIM2_CCMR2_OC2M0;
    TIM2_CCR2H = 0;
    TIM2_CCR2L = 0;
    PORT(SSR1_PORT, DDR) |= SSR1_PIN;
    PORT(SSR1_PORT, CR1) |= SSR1_PIN;
    TIM2_CCER2 |= TIM2_CCER2_CC3E;
    TIM2_CCMR3 |= (TIM2_CCMR2_OC2M1 | TIM2_CCMR2_OC2M2);
    TIM2_CCMR3 &= ~TIM2_CCMR2_OC2M0;
    TIM2_CCR3H = 0;
    TIM2_CCR3L = 0;
    TIM2_CR1 |= TIM2_CR1_CEN;

    /* EXTI1 BUTTON setup */
    extiButton = 0;
    PB_CR2 = PIN4;
    EXTI_CR1 &= ~0x0C;
    EXTI_CR1 |= 0x08;

    rim();


    if (!lcd12864_init(true))
    {
        while (1)
            ;
    }
    struct LCD12864_SEGMENT *lcdTitle = lcd12864_new_segment(0, 1, 1, 1, 1, '#');
    struct LCD12864_SEGMENT *lcdTime = lcd12864_new_segment(1, 2, 2, 1, 1, ' ');
    struct LCD12864_SEGMENT *lcdPowerTemp = lcd12864_new_segment(3, 2, 3, 1, 1, ' ');
    struct LCD12864_SEGMENT *lcdStatus = lcd12864_new_segment(6, 1, 2, 1, 1, '#');

    beep_init();
    uart_init();
    putstring("\r\n\r\n");

    max6675_init();

    do
    {
        volatile uint16_t currentTicks = tim1Value;
        volatile uint8_t currentButton = extiButton;
        volatile uint16_t currentTemperature = (max6675_read() / 4);
        extiButton = 0;
        volatile uint16_t currentSecond = (currentTicks / 4);
        volatile bool isOneSecondInterval = false;

        if (previousTicks != currentTicks)
        {
            previousTicks = currentTicks;
            if (previousSecond != currentSecond)
            {
                previousSecond = currentSecond;
                isOneSecondInterval = true;
                if (profileTimerRunning)
                    profileTimer++;
            }
            if (beeps)
            {
                if ((currentTicks % 2) == 0)
                {
                    beep_on();
                    beepOn = true;
                }
                else if (beepOn)
                {
                    beep_off();
                    beepOn = false;
                    beeps--;
                }
            }
        }

        if (currentButton && stateMachine == SM_NULL)
        {
            stateMachine = SM_GO_RUN;
        }
        else if (currentButton && stateMachine == SM_DONE_Q)
        {
            stateMachine = SM_GO_NULL;
        }
        else if (currentButton && stateMachine > SM_NULL && stateMachine < SM_START_COOLING)
        {
            beeps += 2;
            stateMachine = SM_START_COOLING;
        }
        else if (currentTemperature > DEFAULT_TEMP_HOT && stateMachine < SM_GO_RUN)
        {
            setText(true, false, lcdStatus, "%s %uC", ST_START_HOT, currentTemperature);
            beeps += 2;
            stateMachine = SM_START_COOLING;
        }

        if (currentTemperature == 0 && stateMachine > SM_GO_NULL)
        {
            setText(true, false, lcdStatus, "%s", ST_THERMOCOUPLE_ERROR);
            beeps += 4;
            stateMachine = SM_START_COOLING;
        }
        else if (currentTemperature >= DEFAULT_TEMP_HOT)
        {
            PORT(LED0_PORT, ODR) &= ~LED0_PIN;
        }
        else if (currentTemperature < DEFAULT_TEMP_COOL)
        {
            PORT(LED0_PORT, ODR) |= LED0_PIN;
        }

        if (currentTemperature > DEFAULT_MAX_TEMP && stateMachine < SM_START_COOLING)
        {
            setText(true, false, lcdStatus, "%s", ST_OVERTEMP);
            beeps += 4;
            stateMachine = SM_START_COOLING;
        }

        switch (stateMachine)
        {
        case SM_GO_NULL:
            setText(true, true, lcdTitle, " %s %s", ST_TITLE, ST_VER);
            setText(true, false, lcdStatus, "%s", ST_PRESS_BUTTON_TO_START);
            isHeating = false;
            profileStep = 0;
            displayTime = DISPLAY_CURRENT_SECOND;
            beeps = 0;
            beep_off();
            stateMachine = SM_NULL;

        case SM_NULL:
            break;

        case SM_GO_RUN:
            setText(true, true, lcdTitle, " %s", ST_RUN);
            lcd12864_clear_segment(lcdStatus);
            profileTimer = 0;
            profileTimerRunning = false;
            desiredTemperature = profile[profileStep][PROFILE_TEMP] + PROFILE_OVERSHOOT;
            displayTime = DISPLAY_PROFILE_TIMER;
            beeps += 1;
            isHeating = true;
            stateMachine = SM_RUN;

        case SM_RUN:
            if (!isOneSecondInterval)
                break;

            currentPidDutyCycle = update_pid(&pid, pid_guard(desiredTemperature, currentTemperature), currentTemperature);

            if ((profileTimerRunning == false) && (profile[profileStep][PROFILE_TEMP] - PROFILE_ADJUST <= currentTemperature))
            {
                desiredTemperature = profile[profileStep][PROFILE_TEMP] + PROFILE_ADJUST;
                profileTimer = 0;
                profileTimerRunning = true;
            }
            if ((profileTimerRunning == true) && (profile[profileStep][PROFILE_TIME] <= profileTimer))
            {
                beeps += 1;
                if (++profileStep == PROFILE_LEN)
                    stateMachine = SM_START_COOLING;
                else
                    stateMachine = SM_GO_RUN;
            }
            break;

        case SM_START_COOLING:
            setText(true, true, lcdTitle, " %s", ST_COOLING);
            isHeating = false;
            profileTimerRunning = true;
            profileTimer = 0;
            displayTime = DISPLAY_PROFILE_TIMER;
            beeps += 2;
            stateMachine = SM_COOLING;

        case SM_COOLING:
            if (isOneSecondInterval)
            {
                if (currentTemperature < DEFAULT_TEMP_HOT && profileTimer >= 1)
                {
                    isHeating = false;
                    stateMachine = SM_DONE;
                }
            }
            break;

        case SM_DONE:
            setText(true, true, lcdTitle, " %s", ST_DONE);
            setText(true, false, lcdStatus, "%s", ST_PRESS_TO_RESTART);
            isHeating = false;
            beeps += 6;
            stateMachine = SM_DONE_Q;

        case SM_DONE_Q:

            break;
        }

        if (isHeating)
        {
            if (previousPidDutyCycle != currentPidDutyCycle)
            {
                previousPidDutyCycle = currentPidDutyCycle;
                currentDutyCycle[ELEMENT_TOP] = currentPidDutyCycle * BIAS_T / BIAS_MAX;
                currentDutyCycle[ELEMENT_BOTTOM] = currentPidDutyCycle * BIAS_B / BIAS_MAX;
                setOutput(currentDutyCycle[ELEMENT_TOP], currentDutyCycle[ELEMENT_BOTTOM]);
            }
        }
        else
        {
            if (previousPidDutyCycle != 0)
            {
                setOutput(0, 0);
                previousDutyCycle[ELEMENT_TOP] = 0;
                previousDutyCycle[ELEMENT_BOTTOM] = 0;
            }
        }

        if (isOneSecondInterval)
        {
            lcd12864_clear_segment(lcdTime);
            lcd12864_clear_segment(lcdPowerTemp);

            if (stateMachine == SM_DONE_Q)
            { /*
                format_sprintf(oledTime->buffer, ((learningFailed) ? ST_FAILED : ((learningAborted) ? ST_ABORTED : ST_SUCCESS)));
                if (learningFailed)
                    format_sprintf(oledPowerTemp->buffer, "%s #%04u", ST_ERROR, learningFailed);
                else if (!learningAborted)
                    format_sprintf(oledPowerTemp->buffer, "%2u %3u %3u", learnedDutyCycle, learnedInertia, learnedInsulation);
             */
            }
            else
            {
                uint16_t dT = (displayTime == DISPLAY_CURRENT_SECOND) ? currentSecond : ((displayTime == DISPLAY_COUNTDOWN_TIMER) ? countdownTimer : profileTimer);
                uint16_t lm = (dT / 60);
                uint16_t tm = (lm % 60);
                uint8_t th = (lm / 60);
                uint8_t ts = (dT % 60);
                format_sprintf(lcdTime->buffer, "%c  %02u:%02u:%02u", (uint8_t)displayType, th, tm, ts);
                format_sprintf(lcdPowerTemp->buffer, "--:-- %3u C", currentTemperature);
                if (isHeating)
                    format_sprintf(lcdPowerTemp->buffer, "%02u:%02u", currentDutyCycle[ELEMENT_TOP], currentDutyCycle[ELEMENT_BOTTOM]);
            }

            lcd12864_display_segment(lcdTitle);
            lcd12864_display_segment(lcdTime);
            lcd12864_display_segment(lcdPowerTemp);
            lcd12864_display_segment(lcdStatus);
        }

        wfi();
    } while (1);
}
