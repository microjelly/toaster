#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "oled.h"
#include "font.h"

struct SEGMENT *oled_new_segment(uint8_t page0, uint8_t fontWidth, uint8_t fontHeight, uint8_t fontSpacing, uint8_t rows, uint8_t clearChar)
{

    struct SEGMENT *pSeg = malloc(sizeof(struct SEGMENT));
    if (!pSeg)
        return NULL;

    pSeg->page0 = page0;
    pSeg->fontWidth = fontWidth;
    pSeg->fontHeight = fontHeight;
    pSeg->rows = rows;
    pSeg->clearChar = clearChar;
    pSeg->fontSpacing = fontSpacing;
    pSeg->bufferDepth = (OLED_LCDWIDTH / ((fontWidth * _FONT_W) + fontSpacing)) * rows;
    pSeg->cols = pSeg->bufferDepth / rows;
    if ((!pSeg->buffer) && !(pSeg->buffer = (uint8_t *)malloc(pSeg->bufferDepth)))
    {
        oled_free_segment(pSeg);
        return NULL;
    }

    oled_clear_segment(pSeg);
    return pSeg;
}