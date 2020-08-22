
#include <stdbool.h>
#include <stdlib.h>
#include "oled.h"


bool oled_free_segment(struct SEGMENT *segment)
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