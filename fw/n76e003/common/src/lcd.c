#include <stdbool.h>
#include "lcd.h"

bool lcd_init(bool reset)
{
    /* Initialize CS pin HIGH */
    P11_PushPull_Mode;
    set_P11;

    /* Initialize RES pin HIGH */
    P17_PushPull_Mode;
    set_P17;

    /* Initialize DC pin LOW */
    P03_PushPull_Mode;
    clr_P03;

    /* Initialize spi */
    spi_init();

    if (reset)
    {
        //lcd_command1(LCD_RESET); // Clear Bias: bias 0
        set_P17;
        Timer0_Delay1ms(1);
        clr_P17;
        Timer0_Delay1ms(1);
        set_P17;
        Timer0_Delay1ms(5);
    }

    //lcd_command1(0xA1); // Reverse direction (SEG131-SEG0)
    //lcd_command1(0xC8); // SHL 1,COM63-COM0
    lcd_command1(0xA2); // Clear Bias: bias 0

    // Power_Control 4 (internal converter ON) + 2 (internal regulator ON) + 1 (internal follower ON)
    lcd_command1(0x28 | 0x07); // Power Control

    //  Regulator resistor select
    //            1+Rb/Ra  Vo=(1+Rb/Ra)Vev    Vev=(1-(63-a)/162)Vref   2.1v
    //            0  3.0       4  5.0(default)
    //            1  3.5       5  5.5
    //            2  4         6  6
    //            3  4.5       7  6.4
    //
    lcd_command1(0x20 | 0x05); // Regulator resistor

    // a(0-63) 32=default   Vev=(1-(63-a)/162)Vref   2.1v
    lcd_command1(0x81); // Set Contrast
    lcd_command1(21);
    lcd_command1(0x40); // DisplayLine=0
    lcd_clear(0x00);    //was 00
    lcd_command1(0xAF); // Display ON

    return true;
}

void lcd_command1(uint8_t c)
{
    LCD_TRANSACTION_START
    LCD_MODE_COMMAND
    spi_write(c);
    LCD_TRANSACTION_END
}

void lcd_command_list(const uint8_t *c, uint8_t n)
{
    LCD_TRANSACTION_START
    LCD_MODE_COMMAND
    for (uint8_t i = 0; i < n; i++)
        spi_write(c[i]);
    LCD_TRANSACTION_END
}

void lcd_clear(uint8_t d)
{
    for (uint8_t page = 0; page < 8; page++)
    {
        uint8_t dlist1[] = {
            0x40 | LCD_PIX_START,
            0xB0 | page,
            0x10,
            (0x0f & 0x00)}; // 0x04 is offset foir normal; 0x00 for upsidedown
        lcd_command_list(dlist1, sizeof(dlist1));
        LCD_TRANSACTION_START
        LCD_MODE_DATA
        for (uint8_t idx = 0; idx < 128; idx++)
            spi_write(d);
        LCD_TRANSACTION_END
    }
}

bool lcd_clear_segment(struct LCD_SEGMENT *segment)
{
    memset(segment->buffer, segment->clearChar, segment->bufferDepth);
    return true;
}

__xdata uint8_t spiBuffer[128];
bool lcd_display_segment(struct LCD_SEGMENT *segment)
{
    uint8_t *sBuffer = (uint8_t *)segment->buffer;
    uint8_t cols = segment->bufferDepth / segment->rows;
    uint8_t spiIdx, rb_now, rbit, rpix2, glyph = 0x00;
    uint16_t glyphP = 0x00;
    uint8_t spiDepth = cols * ((segment->fontWidth * _FONT_W) + segment->fontSpacing);
    memset(spiBuffer, 0x00, spiDepth);

    // row by row
    for (uint8_t row = 0; row < segment->rows; row++)
    {
        for (uint8_t fH_now = 0; fH_now < segment->fontHeight; fH_now++)
        {
            uint8_t dlist1[] = {
                0x40 | LCD_PIX_START,
                0xB0 | (segment->page0 + row + fH_now),
                0x10,
                (0x0f & 0x00)}; // |0x04 is offset for normal; 0x00 for upsidedown
            lcd_command_list(dlist1, sizeof(dlist1));

            spiIdx = 0;
            rb_now = _FONT_H * fH_now;
            for (uint8_t col = 0; col < cols; col++)
            {
                glyph = sBuffer[(row * cols) + col];
#ifdef FONTSET_MINI
                if (glyph < 0x20 || glyph > 0x60)
                    glyph = 0x00;
                else
                    glyph -= 0x20;
#endif
                glyphP = glyph * _FONT_W;
                for (uint8_t fw = 0; fw < _FONT_W; fw++)
                {
                    uint8_t line = _font[glyphP + fw];
                    if (segment->fontHeight > 1)
                    {
                        uint8_t new_line = 0x00;
                        for (uint8_t idx_now = 0; idx_now < 8; idx_now++)
                        {
                            rbit = rb_now + idx_now;
                            rpix2 = (rbit / segment->fontHeight);
                            if ((line & (1 << rpix2)))
                                new_line |= (1 << idx_now);
                        }
                        line = new_line;
                    }
                    for (uint8_t fW_now = 0; fW_now < segment->fontWidth; fW_now++)
                    {
                        spiBuffer[spiIdx++] = line;
                    }
                }
                for (uint8_t fs = 0; fs < segment->fontSpacing; fs++)
                {
                    spiBuffer[spiIdx++] = 0x00;
                }
            }
            LCD_TRANSACTION_START
            LCD_MODE_DATA
            for (uint8_t idx = 0; idx < spiDepth; idx++)
                spi_write(spiBuffer[idx]);
            LCD_TRANSACTION_END
        }
    }

    return true;
}