#include "eeprom.h"

void eeprom_lock() {
    FLASH_IAPSR &= ~FLASH_IAPSR_DUL;
}