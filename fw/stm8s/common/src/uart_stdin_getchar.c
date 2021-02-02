#include "uart.h"
#include "uart_stdin.h"

/*
 * Redirect stdin to UART
 */
int getchar()
{
    return uart_read();
}