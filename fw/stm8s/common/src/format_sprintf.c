#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include "format.h"

void format_sprintf(uint8_t *str, uint8_t *format, ...)
{
    va_list args;
    va_start(args, format);
    format_vsprintf(str, format, args);
    va_end(args);
}
