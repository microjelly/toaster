#ifndef LCD12864_H
#define LCD12864_H

#include "stdint.h"
#include "stdbool.h"
#include "stm8s.h"

/*
 * Initialize LCD12864.
 *
 * Pinout:
 * SCK  -> PC5 [spi]
 * MOSI -> PC6 [spi]
 * MISO -> PC7 [spi]
 * CS   -> PC4
 * RES  -> PC3
 * DC   -> PD2
 */

#define LCD12864_TRANSACTION_START         \
    SPI_CR1 = SPI_CR1_MSTR | SPI_CR1_BR(0) | SPI_CR1_SPE; \
    PC_ODR &= ~PIN4;
#define LCD12864_TRANSACTION_END           \
    while ((SPI_SR & SPI_SR_BSY)) \
        ;                         \
    PC_ODR |= PIN4;               \
    SPI_CR1 &= ~SPI_CR1_SPE;
#define LCD12864_MODE_COMMAND PD_ODR &= ~PIN2;
#define LCD12864_MODE_DATA PD_ODR |= PIN2;

#define LCD12864_NORMALDISPLAY 0xA7
#define LCD12864_INVERTDISPLAY 0xA6
#define LCD12864_CLEARON 0xA5
#define LCD12864_CLEAROFF 0xA4
#define LCD12864_RESET 0xE2

#define LCD12864_LCDWIDTH 128
#define LCD12864_LCDHEIGHT 64
#define LCD12864_PIX_START 0

struct LCD12864_SEGMENT
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

bool lcd12864_init(bool reset);
void lcd12864_invert_display(bool i);
void lcd12864_clear_display(bool i);
struct LCD12864_SEGMENT *lcd12864_new_segment(uint8_t page0, uint8_t fontWidth, uint8_t fontHeight, uint8_t fontSpacing, uint8_t rows, uint8_t clearChar);
bool lcd12864_free_segment(struct LCD12864_SEGMENT *segment);
bool lcd12864_clear_segment(struct LCD12864_SEGMENT *segment);
bool lcd12864_display_segment(struct LCD12864_SEGMENT *segment);

void lcd12864_clear(uint8_t d);

void lcd12864_command1(uint8_t c);
void lcd12864_command_list(const uint8_t *c, uint8_t n);

#endif /* LCD12864_H */