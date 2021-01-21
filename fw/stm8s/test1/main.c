/*
 * STM8S-TOASTER
 *
 * LED
 *  LED0 -> PB5 (RED; HOT)
 * SSR
 *  SSR0 -> PD3 [tim2-ch2] > TOP
 *  SSR1 -> PA3 [tim2-ch3] > BOTTOM
 * SW
 *  SW0  -> PB4
 * OLED
 *  CS   -> PC4
 *  DC   -> PD2
 *  RES  -> PC3
 *  SCK  -> PC5 [spi]
 *  MOSI -> PC6 [spi]
 * MAX6675
 *  CS   -> PA1
 *  SCK  -> PC5 [spi]
 *  MISO -> PC7 [spi]
 * BEEP
 *  BEEP -> PD4
 * UART1
 *  TX   -> PD5
 *  RX   -> PD6
 */
#include <stdint.h>
#include <stdbool.h>
#include <stm8s.h>
#include <format.h>
#include <clock.h>
#include <uart_stdout.h>
#include <uart.h>
#include <lcd12864.h>
#include <max6675.h>
#include <beep.h>

#include "defaults.h"

/* TIM1 Update/Overflow interrupt handling routine */
static volatile uint16_t tim1Value;
void TIM1_update(void) __interrupt(TIM1_OVR_UIF_IRQ)
{
    tim1Value++;
    TIM1_SR1 &= ~TIM_SR1_UIF;
}

int main(void)
{
    volatile uint16_t previousTicks = 0xffff;
    volatile uint16_t previousSecond = 0xffff;
    volatile uint8_t beeps = 2;
    volatile bool beepOn = false;
    //    volatile bool iNvert = true;

    sim();
    clock_init();
    uart_init();
    max6675_init();
    beep_init();

    /* LED setup */
    PORT(LED0_PORT, DDR) |= LED0_PIN;
    PORT(LED0_PORT, CR1) |= LED0_PIN;

    /* TIM1 setup ~250ms */
    tim1Value = 0;
    TIM1_PSCRH = 0x10;
    TIM1_PSCRL = 0x00;
    TIM1_ARRH = 0x03;
    TIM1_ARRL = 0xd0;
    TIM1_IER |= TIM_IER_UIE;
    TIM1_CR1 |= TIM_CR1_CEN;

    rim();
    
    putstring("\r\nTEST1\r\n\r\n");
    
    
    lcd12864_init(true);
    struct LCD12864_SEGMENT *lcdTitle = lcd12864_new_segment(0, 1, 1, 1, 1, '#');
    struct LCD12864_SEGMENT *lcdTime = lcd12864_new_segment(1, 2, 2, 1, 1, ' ');
    struct LCD12864_SEGMENT *lcdPowerTemp = lcd12864_new_segment(3, 2, 3, 1, 1, ' ');
    struct LCD12864_SEGMENT *lcdStatus = lcd12864_new_segment(6, 1, 2, 1, 1, '#');

    do
    {
        volatile uint16_t currentTicks = tim1Value;
        volatile uint16_t currentSecond = (currentTicks / 4);
        volatile bool isOneSecondInterval = false;

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
                    beep_on();
                    PORT(LED0_PORT, ODR) &= ~LED0_PIN;
                    beepOn = true;
                }
                else if (beepOn)
                {
                    beep_off();
                    PORT(LED0_PORT, ODR) |= LED0_PIN;
                    beepOn = false;
                    beeps--;
                }
            }
        }

        if (isOneSecondInterval)
        {
            
            uint16_t dT = currentSecond;
            volatile uint16_t currentTemperatureRaw = max6675_read();
            volatile uint16_t currentTemperature = currentTemperatureRaw / 4;
            volatile uint16_t currentTemperaturePoint = (currentTemperatureRaw - (currentTemperature * 4)) * 100;
            uint16_t lm = (dT / 60);
            uint16_t tm = (lm % 60);
            uint8_t th = (lm / 60);
            uint8_t ts = (dT % 60);

            format_sprintf(lcdTime->buffer, "? %02u:%02u:%02u", th, tm, ts);
            format_sprintf(lcdPowerTemp->buffer, "--:-- %3u C", currentTemperature);

            uint8_t *ptr = lcdTime->buffer;
            putstring(ptr);
            putstring(" ");
            ptr = lcdPowerTemp->buffer;
            putstring(ptr);
            putstring("\r\n");

            lcd12864_display_segment(lcdTitle);
            lcd12864_display_segment(lcdTime);
            lcd12864_display_segment(lcdPowerTemp);
            lcd12864_display_segment(lcdStatus);
        }

        wfi();
    } while (1);
}
