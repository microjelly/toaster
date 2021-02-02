#ifndef OLED_H
#define OLED_H

#include "stdint.h"
#include "stdbool.h"
#include "stm8s.h"

/*
 * Initialize OLED.
 *
 * Pinout:
 * SCK  -> PC5 [spi]
 * MOSI -> PC6 [spi]
 * MISO -> PC7 [spi]
 * CS   -> PC4
 * RES  -> PC3
 * DC   -> PD6
 */

struct SEGMENT
{
    uint8_t fontWidth;
    uint8_t fontHeight;
    uint8_t fontSpacing;
    uint8_t rows;
    uint8_t cols;
    uint8_t width;
    uint8_t height;
    uint8_t *buffer;
    uint16_t bufferDepth;
    uint8_t page0;
    uint8_t clearChar;
};

bool oled_init(uint8_t vcs, bool reset);
struct SEGMENT *oled_new_segment(uint8_t page0, uint8_t fontWidth, uint8_t fontHeight, uint8_t fontSpacing, uint8_t rows, uint8_t clearChar);
bool oled_free_segment(struct SEGMENT *segment);
bool oled_clear_segment(struct SEGMENT *segment);
bool oled_display_segment(struct SEGMENT *segment);
void oled_clear_display(void);
void oled_invert_display(bool i);
void oled_dim_display(bool dim);

void oled_command_list(const uint8_t *c, uint8_t n);
void oled_command1(uint8_t c);

#if defined SSD1306_128_64
#define OLED_LCDWIDTH 128
#define OLED_LCDHEIGHT 64
#define OLED_PIX_START 0
#endif
#if defined SSD1306_128_32
#define OLED_LCDWIDTH 128
#define OLED_LCDHEIGHT 32
#define OLED_PIX_START 0
#endif
#if defined SH1106_128_64
#define OLED_LCDWIDTH 128
#define OLED_LCDHEIGHT 64
#define OLED_PIX_START 2
#endif

#ifndef OLED_LCDWIDTH
#define OLED_LCDWIDTH 128
#define OLED_LCDHEIGHT 64
#define OLED_PIX_START 0
#endif

#define SSD1306_BLACK 0   ///< Draw 'off' pixels
#define SSD1306_WHITE 1   ///< Draw 'on' pixels
#define SSD1306_INVERSE 2 ///< Invert pixels

#define TRANSACTION_START         \
    SPI_CR1 = SPI_CR1_MSTR | SPI_CR1_BR(0) | SPI_CR1_SPE; \
    PC_ODR &= ~PIN4;
#define TRANSACTION_END           \
    while ((SPI_SR & SPI_SR_BSY)) \
        ;                         \
    PC_ODR |= PIN4;               \
    SPI_CR1 &= ~SPI_CR1_SPE;
#define OLED_MODE_COMMAND PD_ODR &= ~PIN6;
#define OLED_MODE_DATA PD_ODR |= PIN6;

#define SSD1306_EXTERNALVCC 0x01  ///< External display voltage source
#define SSD1306_SWITCHCAPVCC 0x02 ///< Gen. display voltage from 3.3V

#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR 0x22
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_SETCONTRAST 0x81
#define SSD1306_CHARGEPUMP 0x8D
#define SSD1306_SEGREMAP 0xA0
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETVCOMDETECT 0xDB

#endif /* OLED_H */