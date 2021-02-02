#include "uart.h"
#include "stm8s.h"

void uart_init() {
    /* round to nearest integer */
    uint16_t div = (F_CPU + BAUDRATE / 2) / BAUDRATE;
    /* madness.. */
    UART1_BRR2 = ((div >> 8) & 0xF0) + (div & 0x0F);
    UART1_BRR1 = div >> 4;
    /* enable transmitter and receiver */
    UART1_CR2 = UART_CR2_TEN | UART_CR2_REN;
}