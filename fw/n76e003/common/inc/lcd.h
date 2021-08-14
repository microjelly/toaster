#ifndef LCD_H
#define LCD_H

#include <stdlib.h>
#include <string.h>

#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "spi.h"
#include "font.h"

/*
 * Initialize LCD.
 *
 * Pinout:
 *  CS   -> P1.1
 *  DC   -> P0.3
 *  RES  -> P1.7
 *  SCK  -> P1.0;SPCLK [spi]
 *  MOSI -> P0.0;MOSI  [spi]
 */

#define LCD_TRANSACTION_START clr_P11;
#define LCD_TRANSACTION_END set_P11;

#define LCD_MODE_COMMAND clr_P03;
#define LCD_MODE_DATA set_P03;

#define LCD_NORMALDISPLAY 0xA7
#define LCD_INVERTDISPLAY 0xA6
#define LCD_CLEARON 0xA5
#define LCD_CLEAROFF 0xA4
#define LCD_RESET 0xE2

#define LCD_LCDWIDTH 128
#define LCD_LCDHEIGHT 64
#define LCD_PIX_START 0

typedef struct LCD_SEGMENT
{
    uint8_t clearChar;
    uint8_t **buffer;
    uint16_t bufferDepth;
    uint8_t fontWidth;
    uint8_t fontHeight;
    uint8_t fontSpacing;
    uint8_t page0;
    uint8_t rows;
};

bool lcd_init(bool reset);
bool lcd_clear_segment(struct LCD_SEGMENT *segment);
bool lcd_display_segment(struct LCD_SEGMENT *segment);

void lcd_command1(uint8_t c);
void lcd_command_list(const uint8_t *c, uint8_t n);
void lcd_clear(uint8_t d);

#endif /* LCD_H */