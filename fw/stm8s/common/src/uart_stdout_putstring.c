#include "uart.h"
#include "uart_stdout.h"

void putstring(uint8_t *str)
{
    while (*str !=0)
    {
        putchar(*str++);
    }
}