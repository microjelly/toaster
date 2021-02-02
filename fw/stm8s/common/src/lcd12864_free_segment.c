#include <stdbool.h>
#include <stdlib.h>
#include "lcd12864.h"

bool lcd12864_free_segment(struct LCD12864_SEGMENT *segment)
{
    if (segment->buffer)
    {
        free(segment->buffer);
        segment->buffer = NULL;
    }
    if (segment)
    {
        free(segment);
        segment = NULL;
    }

    return true;
}