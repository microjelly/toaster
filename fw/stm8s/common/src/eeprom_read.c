#include "eeprom.h"

void eeprom_read(uint16_t addr, uint8_t *buf, int len) {
    for (int i = 0; i < len; i++, addr++)
        buf[i] = (*(volatile uint8_t *)(addr));
}