/*
 * N76E003-TEST1
 *
 * LED
 *  LED0 -> P1.4 (RED; HOT)
 * SSR
 *  SSR0 -> P0.4;PWM3 > TOP
 *  SSR1 -> P1.5;PWM5 > BOTTOM
 * SERVO
 *  SRV0 -> P1.2;PWM0
 * SW
 *  SW0  -> P1.3
 * LCD
 *  CS   -> P1.1
 *  DC   -> P0.3
 *  RES  -> P1.2
 *  SCK  -> P1.0;SPCLK [spi]
 *  MOSI -> P0.0;MOSI  [spi]
 * MAX6675
 *  CS   -> P3.0
 *  SCK  -> P1.0;SPCLK [spi]
 *  MISO -> P0.1;MISO  [spi]
 * BEEP
 *  BEEP -> P0.5;T0
 * UART1
 *  TX   -> P0.6
 *  RX   -> P0.7
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
/*==========================================================================*/
void main(void)
{
	uint16_t previousTicks = 0xffff;
	uint16_t previousSecond = 0xffff;
	uint8_t servo0 = SRV0_START;
	uint8_t beeps = 2;
	bool beepOn = false;

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
	//PWM_CENTER_TYPE;
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
		lcdTimeBuffer,		   // buffer
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

	printf_tiny("\r\nTEST1\r\n");
	setOutput(24, 49);

	do
	{
		uint8_t currentSW0 = sw0Counter;
		sw0Counter = 0;
		uint16_t currentTicks = tim2Value;
		uint16_t currentSecond = (currentTicks / 4);
		bool isOneSecondInterval = false;

		if (previousTicks != currentTicks)
		{
			previousTicks = currentTicks;
			if (previousSecond != currentSecond)
			{
				previousSecond = currentSecond;
				isOneSecondInterval = true;
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

		if (currentSW0)
		{
			beeps += 2;
		}

		if (isOneSecondInterval)
		{
			lcd_clear_segment(&lcdTime);
			lcd_clear_segment(&lcdPowerTemp);

			uint16_t dT = currentSecond;
			uint16_t currentTemperatureRaw = max6675_read();
			uint16_t currentTemperature = currentTemperatureRaw / 4;
			uint16_t currentTemperaturePoint = (currentTemperatureRaw - (currentTemperature * 4)) * 100;
			uint16_t lm = (dT / 60);
			uint16_t tm = (lm % 60);
			uint8_t th = (lm / 60);
			uint8_t ts = (dT % 60);

			servo0 += 15;
			if (servo0 > 180)
			{
				servo0 = SRV0_START;
			}
			uint16_t pos0 = setServo(servo0);

			printf_tiny("%d:%d:%d > %d\r\n", th, tm, ts, pos0);

			sprintf(lcdTimeBuffer, "? %02u:%02u:%02u", th, tm, ts);
			sprintf(lcdPowerTempBuffer, "--:-- %3u C", currentTemperature);
			LED0 = !LED0;

			lcd_display_segment(&lcdTitle);
			lcd_display_segment(&lcdTime);
			lcd_display_segment(&lcdPowerTemp);
			lcd_display_segment(&lcdStatus);
		}

		set_IDL;
	} while (1);
}
