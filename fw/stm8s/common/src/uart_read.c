#include "uart.h"
#include "stm8s.h"

uint8_t uart_read() {
    while (!(UART1_SR & UART_SR_RXNE));
    return UART1_DR;
}