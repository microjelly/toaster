#ifndef FORMAT_H
#define FORMAT_H

#include <stdint.h>
#include <stdarg.h>

void format_vsprintf(uint8_t *str, uint8_t *format, va_list args);
void format_sprintf(uint8_t *str, uint8_t *format, ...);

#endif /* FORMAT_H */