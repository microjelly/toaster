#include "uart.h"
#include "stm8s.h"

void uart_write(uint8_t data) {
    UART1_DR = data;
    while (!(UART1_SR & UART_SR_TC));
}
