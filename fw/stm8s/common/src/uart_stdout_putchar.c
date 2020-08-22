#include "uart.h"
#include "uart_stdout.h"

/*
 * Redirect stdout to UART
 */
int putchar(int c)
{
    uart_write(c);
    return 0;
}