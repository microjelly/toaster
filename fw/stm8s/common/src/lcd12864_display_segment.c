#include <stdlib.h>
#include <string.h>
#include "lcd12864.h"
#include "font.h"
#include "spi.h"

bool lcd12864_display_segment(struct LCD12864_SEGMENT *segment)
{

    if (!segment)
        return false;

    // allocate spi buffer (for page)
    uint8_t spiDepth = segment->cols * ((segment->fontWidth * _FONT_W) + segment->fontSpacing);
    uint8_t *spiBuffer = (uint8_t *)malloc(spiDepth);
    if (!spiBuffer)
        return false;
    memset(spiBuffer, 0x00, spiDepth);

    uint8_t spiIdx, rb_now, rbit, rpix2, glyph = 0x00;
    uint16_t glyphP = 0x00;
    uint8_t seg_fH = segment->fontHeight;
    // row by row
    for (uint8_t row = 0; row < segment->rows; row++)
    {
        for (uint8_t fH_now = 0; fH_now < seg_fH; fH_now++)
        {
            uint8_t dlist1[] = {
                0x40 | LCD12864_PIX_START,
                0xB0 | (segment->page0 + row + fH_now),
                (0x10 | (0 >> 4)),
                (0x0f & 0) | 0x04};
            lcd12864_command_list(dlist1, sizeof(dlist1));
 
            spiIdx = 0;
            rb_now = _FONT_H * fH_now;
            for (uint8_t col = 0; col < segment->cols; col++)
            {
                glyph = segment->buffer[(row * segment->cols) + col];
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
                    if (seg_fH > 1)
                    {
                        uint8_t new_line = 0x00;
                        for (uint8_t idx_now = 0; idx_now < 8; idx_now++)
                        {
                            rbit = rb_now + idx_now;
                            rpix2 = (rbit / seg_fH);
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
            // push page to display
            LCD12864_TRANSACTION_START
            LCD12864_MODE_DATA
            for (uint8_t idx = 0; idx < spiDepth; idx++)
                spi_write(spiBuffer[idx]);
            LCD12864_TRANSACTION_END
        }
    }

    if (spiBuffer)
    {
        free(spiBuffer);
        spiBuffer = NULL;
    }

    return true;
}