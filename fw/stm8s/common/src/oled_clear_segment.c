
#include <stdbool.h>
#include <string.h>
#include "oled.h"

bool oled_clear_segment(struct SEGMENT *segment)
{
    if (!segment)
        return false;

    memset(segment->buffer, segment->clearChar, segment->bufferDepth);

    return true;
}