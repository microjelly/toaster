#include "eeprom.h"

void eeprom_write(uint16_t addr, uint8_t *buf, uint16_t len) {
    eeprom_unlock();
    for (uint16_t i = 0; i < len; i++, addr++) {
        (*(volatile uint8_t *)(addr)) = buf[i];
        eeprom_wait_busy();
    }
    eeprom_unlock();
}