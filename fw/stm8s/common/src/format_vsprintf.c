#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include "uart_stdout.h"
#include "format.h"

static const uint16_t dv[] = {
    10000,
    1000,
    100,
    10,
    1,
};

static uint8_t xtoa(uint8_t *str, uint16_t x, const uint16_t *dp)
{
    uint8_t len = 0;
    uint8_t c;
    uint16_t d;
    if (x)
    {
        while (x < *dp)
            ++dp;
        do
        {
            d = *dp++;
            c = '0';
            while (x >= d)
                ++c, x -= d;
            *str++ = c;
            len++;
        } while (!(d & 1));
    }
    else
    {
        len++;
        *str++ = (uint8_t)'0';
    }

    *str++ = 0x00;
    return len;
}

void format_vsprintf(uint8_t *str, uint8_t *format, va_list args) {
    uint8_t c, len;
    int16_t i;
    uint8_t *string_temp;
    uint8_t buff[6];

    while (c = *format++)
    {
        bool zl = false;
        uint8_t zs = 0;
        uint8_t cnt = 0;
        if (c == '%')
        {
            if (*format == (uint8_t)'0')
            {
                *format++;
                zl = true;
            }
            if (*format >= (uint8_t)'1' && *format <= (uint8_t)'5')
            {
                zs = (uint8_t)*format - 0x30;
                *format++;
            }

            switch (c = *format++)
            {
            case '%': // %
                *str++ = (uint8_t)'%';
                break;
            case 's': // String
                string_temp = va_arg(args, uint8_t *);
                while (*string_temp != 0)
                {
                    *str++ = *string_temp++;
                }
                break;
            case 'c': // Char
                *str++ = va_arg(args, uint8_t);
                break;
            case 'i': // 16 bit Integer
            case 'u': // 16 bit Unsigned
                i = va_arg(args, int16_t);
                if (c == 'i' && i < 0)
                    i = -i, *str++ = (uint8_t)'-';
                len = xtoa(buff, (uint16_t)i, dv);
                if (zs && (len < zs))
                {
                    while (++len <= zs)
                        *str++ = (zl) ? (uint8_t)'0' : (uint8_t)' ';
                }
                string_temp = &buff[0];
                for (uint8_t index = 0; index <= sizeof(buff); index++)
                    while (*string_temp != 0)
                    {
                        *str++ = *string_temp++;
                    }
                break;
            case 0:
                return;
            default:
                goto bad_fmt;
            }
        }
        else
        {
        bad_fmt:
            *str++ = c;
        }
    }
    *str++ = 0x00;
}