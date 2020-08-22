#ifndef UART_STDOUT_H
#define UART_STDOUT_H

int putchar(int c);
void putstring(uint8_t *str);
void putsf(uint8_t *format, ...);

#endif /* UART_STDOUT_H */