#include <stdbool.h>
#include <string.h>
#include "lcd12864.h"

bool lcd12864_clear_segment(struct LCD12864_SEGMENT *segment)
{
    if (!segment)
        return false;

    memset(segment->buffer, segment->clearChar, segment->bufferDepth);

    return true;
}