/*
 * N76E003-TOASTER
 *
 * LED
 *  LED0 -> [11] P1.4 (RED; HOT)
 * SSR
 *  SSR0 -> [20] P0.4;PWM3 > TOP
 *  SSR1 -> [10] P1.5;PWM5 > BOTTOM
 * SERVO
 *  SRV0 -> [13] P1.2;PWM0
 * SW
 *  SW0  -> [12] P1.3
 * LCD
 *  CS   -> [14] P1.1
 *  DC   -> [19] P0.3
 *  RES  -> [06] P1.7
 *  SCK  -> [15] P1.0;SPCLK [spi]
 *  MOSI -> [16] P0.0;MOSI  [spi]
 * MAX6675
 *  CS   -> [05] P3.0
 *  SCK  -> [15] P1.0;SPCLK [spi]
 *  MISO -> [17] P0.1;MISO  [spi]
 * BEEP
 *  BEEP -> [01] P0.5;T0
 * UART1    115200 8N1
 *  TX   -> [02] P0.6
 *  RX   -> [03] P0.7
 */

#include <N76E003.h>
#include <SFR_Macro.h>
#include <Function_define.h>
#include <Common.h>
#include <Delay.h>
#include <stdbool.h>

#include <max6675.h>
#include <lcd.h>
#include "defaults.h"
#include "strings.h"
#include "pid.h"

/* Needed for printf */
int putchar(int c)
{
	while (!TI)
		;
	TI = 0;
	SBUF = c;
	return c;
}

void TIM0_ISR(void) __interrupt(1)
{
	clr_TF0;
	TL0 = LOBYTE(BUZZER_PERIOD);
	TH0 = HIBYTE(BUZZER_PERIOD);
}

volatile uint16_t tim2Value = 0;
void TIM2_ISR(void) __interrupt(5)
{
	clr_TF2;
	tim2Value++;
}

volatile uint8_t sw0Counter;
void PinInterrupt_ISR(void) __interrupt(7)
{
	if (PIF == 0x08)
	{
		PIF = 0;
		sw0Counter++;
	}
}

void setOutput(uint8_t value0, uint8_t value1)
{
	uint16_t pwm = PWM_SLICE * value0;
	if (pwm > 0)
	{
		PWM3H = HIBYTE(pwm);
		PWM3L = LOBYTE(pwm);
	}
	else
	{
		PWM3H = 0;
		PWM3L = 0;
	}

	pwm = PWM_SLICE * value1;
	if (pwm > 0)
	{
		set_SFRPAGE;
		PWM5H = HIBYTE(pwm);
		PWM5L = LOBYTE(pwm);
		clr_SFRPAGE;
	}
	else
	{
		set_SFRPAGE;
		PWM5H = 0;
		PWM5L = 0;
		clr_SFRPAGE;
	}
	while (LOAD == 1)
		;
	set_LOAD;
}

uint16_t setServo(uint8_t value0)
{
	uint16_t srv0 = (PWM_SLICE * 6) + (value0 * (PWM_SLICE/4));

	PWM0H = HIBYTE(srv0);
	PWM0L = LOBYTE(srv0);
	while (LOAD == 1)
		;
	set_LOAD;
	return srv0;
}

void setText(bool stdout, bool isTitle, struct LCD_SEGMENT *segment, uint8_t *format, ...)
{
    uint8_t *ptr = (uint8_t*)segment->buffer;
    lcd_clear_segment(segment);

    if (isTitle)
    {
        *ptr++;
        *ptr++;
    }

    va_list args;
    va_start(args, format);
    vsprintf(ptr, format, args);
    va_end(args);

    if (stdout)
    {
	   if (isTitle)
            *ptr++;
		printf_tiny("%s: '%s'\r\n", ((isTitle) ? " TITLE" : "STATUS"), ptr);
//        printf_tiny((isTitle) ? "TITLE: '" : "STATUS: '");
//        printf_tiny("%s", ptr);
//        printf_tiny("'\r\n");
    }
}

/*==========================================================================*/
void main(void)
{
	__xdata uint16_t previousTicks = 0xffff;
	__xdata uint16_t previousSecond = 0xffff;
	__xdata uint8_t servo0 = SRV0_START;
	__xdata uint8_t previousDutyCycle[NUMBER_OF_OUTPUTS] = {0, 0};
    __xdata uint8_t currentDutyCycle[NUMBER_OF_OUTPUTS] = {0, 0};

    __xdata bool isHeating = false;
    __xdata uint8_t stateMachine = SM_GO_NULL;
	__xdata uint8_t beeps = 2;
	__xdata bool beepOn = false;

    __xdata uint16_t profileTimer = 0;
    __xdata bool profileTimerRunning = false;
    __xdata uint8_t profileStep = 0;
    __xdata uint16_t desiredTemperature = 0;

    __xdata uint8_t currentPidDutyCycle = 0;
    __xdata uint8_t previousPidDutyCycle = 0xff;

    __xdata uint16_t countdownTimer = 0;
    __xdata uint8_t displayTime = DISPLAY_CURRENT_SECOND;
    __xdata uint8_t displayType = '+';

    __xdata pid_struct pid = {
        0, 0,   //dstate, istate
        10, 0,  //imax, imin  
        99, 0,  //max/min output limits
        PID_P, PID_I, PID_D //p, i, d gains
    };

	clr_EA;

	/* SW0 setup */
	sw0Counter = 0;
	P13_Input_Mode;
	clr_PIPS1;
	set_PIPS0;
	Enable_BIT3_FallEdge_Trig;
	set_EPI;

	/* LED setup */
	P14_Quasi_Mode;

	/* TIM0 setup / BUZZER */
	P05_PushPull_Mode;
	TIMER0_MODE1_ENABLE;
	TL0 = LOBYTE(BUZZER_PERIOD);
	TH0 = HIBYTE(BUZZER_PERIOD);
	set_ET0;
	set_T0OE;
	clr_TR0;

	/* TIM2 setup ~200ms */
	TIMER2_DIV_128;
	TIMER2_Auto_Reload_Delay_Mode;
	RCMP2L = LOBYTE(TIMER_DIV128_VALUE_250ms);
	RCMP2H = HIBYTE(TIMER_DIV128_VALUE_250ms);
	TL2 = 0;
	TH2 = 0;
	set_ET2;
	set_TR2;

	/* PWM setup */
	PWM_IMDEPENDENT_MODE;
	PWM_CENTER_TYPE;
	PWM_CLOCK_DIV_8;
	PWMPH = HIBYTE(PWM_PERIOD);
	PWMPL = LOBYTE(PWM_PERIOD);
	set_PWMRUN;

	/* SSR setup */
	P04_PushPull_Mode;
	P15_PushPull_Mode;
	PWM3_P04_OUTPUT_ENABLE;
	PWM5_P15_OUTPUT_ENABLE;

	/* SERVO setup */
	P12_PushPull_Mode;
	PWM0_P12_OUTPUT_ENABLE;

	/* MAX6675 setup */
	max6675_init();

	/* LCD setup */
	lcd_init(true);

	__xdata uint8_t lcdTitleBuffer[21];
	__xdata struct LCD_SEGMENT lcdTitle = {
		'#',					// clearChar
		lcdTitleBuffer,			// buffer
		sizeof(lcdTitleBuffer), // bufferDepth
		1,						// fontWidth
		1,						// fontHeight
		1,						// fontSpacing
		0,						// page0
		1,						// rows
	};
	lcd_clear_segment(&lcdTitle);
	__xdata uint8_t lcdTimeBuffer[11];
	__xdata struct LCD_SEGMENT lcdTime = {
		' ',				   // clearChar
		&lcdTimeBuffer,		   // buffer
		sizeof(lcdTimeBuffer), // bufferDepth
		2,					   // fontWidth
		2,					   // fontHeight
		1,					   // fontSpacing
		1,					   // page0
		1,					   // rows
	};
	lcd_clear_segment(&lcdTime);

	__xdata uint8_t lcdPowerTempBuffer[11];
	__xdata struct LCD_SEGMENT lcdPowerTemp = {
		' ',						// clearChar
		lcdPowerTempBuffer,			// buffer
		sizeof(lcdPowerTempBuffer), // bufferDepth
		2,							// fontWidth
		3,							// fontHeight
		1,							// fontSpacing
		3,							// page0
		1,							// rows
	};
	lcd_clear_segment(&lcdPowerTemp);

	__xdata uint8_t lcdStatusBuffer[21];
	__xdata struct LCD_SEGMENT lcdStatus = {
		'#',					 // clearChar
		lcdStatusBuffer,		 // buffer
		sizeof(lcdStatusBuffer), // bufferDepth
		1,						 // fontWidth
		2,						 // fontHeight
		1,						 // fontSpacing
		6,						 // page0
		1,						 // rows
	};
	lcd_clear_segment(&lcdStatus);

	/* UART0 setup */
	InitialUART0_Timer3(115200);
	TI = 1;

	set_EA;
	printf_tiny("\r\n\r\n");

	do
	{
		uint8_t currentSW0 = sw0Counter;
		sw0Counter = 0;
		uint16_t currentTicks = tim2Value;
		uint16_t currentTemperatureRaw = max6675_read();
		uint16_t currentTemperature = currentTemperatureRaw / 4;
		uint16_t currentTemperaturePoint = (currentTemperatureRaw - (currentTemperature * 4)) * 100;

		uint16_t currentSecond = (currentTicks / 4);
		bool isOneSecondInterval = false;

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
					set_TR0;
					beepOn = true;
				}
				else if (beepOn)
				{
					clr_TR0;
					beepOn = false;
					beeps--;
				}
			}
		}

        if (currentSW0 && stateMachine == SM_NULL)
        {
            stateMachine = SM_GO_RUN;
        }
        else if (currentSW0 && stateMachine == SM_DONE_Q)
        {
            stateMachine = SM_GO_NULL;
        }
        else if (currentSW0 && stateMachine > SM_NULL && stateMachine < SM_START_COOLING)
        {
            beeps += 2;
            stateMachine = SM_START_COOLING;
        }
        else if (currentTemperature > DEFAULT_TEMP_HOT && stateMachine < SM_GO_RUN)
        {
            setText(true, false, &lcdStatus, "%s %uC", ST_START_HOT, currentTemperature);
            beeps += 2;
            stateMachine = SM_START_COOLING;
        }

        if (currentTemperature == 0 && stateMachine > SM_GO_NULL)
        {
            setText(true, false, &lcdStatus, "%s", ST_THERMOCOUPLE_ERROR);
            beeps += 4;
            stateMachine = SM_START_COOLING;
        }
        else if (currentTemperature >= DEFAULT_TEMP_HOT)
        {
            LED0 = 0;
        }
        else if (currentTemperature < DEFAULT_TEMP_COOL)
        {
            LED0 = 1;
        }

        if (currentTemperature > DEFAULT_MAX_TEMP && stateMachine < SM_START_COOLING)
        {
            setText(true, false, &lcdStatus, "%s", ST_OVERTEMP);
            beeps += 4;
            stateMachine = SM_START_COOLING;
        }

        switch (stateMachine)
        {
        case SM_GO_NULL:
            setText(true, true, &lcdTitle, " %s %s", ST_TITLE, ST_VER);
            setText(true, false, &lcdStatus, "%s", ST_PRESS_BUTTON_TO_START);
            isHeating = false;
            profileStep = 0;
            displayTime = DISPLAY_CURRENT_SECOND;
            beeps = 0;
            clr_TR0;
            stateMachine = SM_NULL;

        case SM_NULL:
            break;

        case SM_GO_RUN:
            setText(true, true, &lcdTitle, " %s", ST_RUN);
            lcd_clear_segment(&lcdStatus);
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
            setText(true, true, &lcdTitle, " %s", ST_COOLING);
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
            setText(true, true, &lcdTitle, " %s", ST_DONE);
            setText(true, false, &lcdStatus, "%s", ST_PRESS_TO_RESTART);
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
                setOutput(currentPidDutyCycle, currentPidDutyCycle);
                currentDutyCycle[ELEMENT_TOP] = currentPidDutyCycle * BIAS_T / BIAS_MAX;
                currentDutyCycle[ELEMENT_BOTTOM] = currentPidDutyCycle * BIAS_B / BIAS_MAX;
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
			lcd_clear_segment(&lcdTime);
            lcd_clear_segment(&lcdPowerTemp);

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
				setText(false, false, &lcdTime,  "%c %02u:%02u:%02u", displayType, th, tm, ts);
				if (isHeating)
					setText(false, false, &lcdPowerTemp, "%02u:%02u %3u C", currentDutyCycle[ELEMENT_BOTTOM], currentDutyCycle[ELEMENT_TOP], currentTemperature);
				else
					setText(false, false, &lcdPowerTemp, "--:-- %3u C", currentTemperature);
				
            }

//			setText(true, false, &lcdTime, "? %02u:%02u:%02u", th, tm, ts);

			lcd_display_segment(&lcdTitle);
			lcd_display_segment(&lcdTime);
			lcd_display_segment(&lcdPowerTemp);
			lcd_display_segment(&lcdStatus);
		}

		set_IDL;
	} while (1);
}
