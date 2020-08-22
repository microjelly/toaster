#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>
#include "stm8s.h"

void eeprom_unlock();
void eeprom_lock();
void eeprom_wait_busy();

void eeprom_read(uint16_t addr, uint8_t *buf, int len);
void eeprom_write(uint16_t addr, uint8_t *buf, uint16_t len);

#endif /* EEPROM_H */