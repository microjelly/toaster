
#include <stdint.h>
#include <stdbool.h>
#include "stm8s.h"
#include "oled.h"
#include "spi.h"
#include "delay.h"

uint8_t _contrast;

bool oled_init(uint8_t vcs, bool reset)
{

    /* Initialize CS pin HIGH */
    PC_DDR |= PIN4;
    PC_CR1 |= PIN4;
    PC_ODR |= PIN4;

    /* Initialize RES pin LOW */
    PC_DDR |= PIN3;
    PC_CR1 |= PIN3;
    PC_ODR &= ~PIN3;

    /* Initialize DC pin LOW */
    PD_DDR |= PIN6;
    PD_CR1 |= PIN6;
    PD_ODR &= ~PIN6;

    /* Initialize spi */
    spi_init();

    if (reset)
    {
        PC_ODR |= PIN3;
        delay_ms(1);
        PC_ODR &= ~PIN3;
        delay_ms(10);
        PC_ODR |= PIN3;
    }

    TRANSACTION_START

    // Init sequence
    static const uint8_t init1[] = {
        SSD1306_DISPLAYOFF,         // 0xAE
        SSD1306_SETDISPLAYCLOCKDIV, // 0xD5
        0x80,                       // the suggested ratio 0x80
        SSD1306_SETMULTIPLEX};      // 0xA8
    oled_command_list(init1, sizeof(init1));
    oled_command1(OLED_LCDHEIGHT - 1);

    static const uint8_t init2[] = {
        SSD1306_SETDISPLAYOFFSET,   // 0xD3
        0x0,                        // no offset
        SSD1306_SETSTARTLINE | 0x0, // line #0
        SSD1306_CHARGEPUMP};        // 0x8D
    oled_command_list(init2, sizeof(init2));
    oled_command1((vcs == SSD1306_EXTERNALVCC) ? 0x10 : 0x14);

    static const uint8_t init3[] = {
        SSD1306_SEGREMAP | 0x1,
        SSD1306_COMSCANDEC};
    oled_command_list(init3, sizeof(init3));

    uint8_t comPins = 0x02;
    uint8_t contrast = 0x8F;

#if ((OLED_LCDWIDTH == 128) && (OLED_LCDHEIGHT == 32))
    comPins = 0x02;
    contrast = 0x8F;
#elif ((OLED_LCDWIDTH == 128) && (OLED_LCDHEIGHT == 64))
    comPins = 0x12;
    contrast = (vcs == SSD1306_EXTERNALVCC) ? 0x9F : 0xCF;
#elif ((OLED_LCDWIDTH == 96) && (OLED_LCDHEIGHT == 16))
    comPins = 0x2;
    contrast = (vcs == SSD1306_EXTERNALVCC) ? 0x10 : 0xAF;
#endif

    oled_command1(SSD1306_SETCOMPINS);
    oled_command1(comPins);
    oled_command1(SSD1306_SETCONTRAST);
    oled_command1(contrast);
    _contrast = contrast;

    oled_command1(SSD1306_SETPRECHARGE); // 0xd9
    oled_command1((vcs == SSD1306_EXTERNALVCC) ? 0x22 : 0xF1);
    static const uint8_t init5[] = {
        SSD1306_SETVCOMDETECT, // 0xDB
        0x40,
        SSD1306_DISPLAYALLON_RESUME, // 0xA4
        SSD1306_NORMALDISPLAY,       // 0xA6
        SSD1306_DEACTIVATE_SCROLL,
        SSD1306_DISPLAYON}; // Main screen turn on
    oled_command_list(init5, sizeof(init5));
    TRANSACTION_END

    oled_clear_display();

    return true;
}