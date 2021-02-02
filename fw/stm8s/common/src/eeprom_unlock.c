#include "eeprom.h"

void eeprom_unlock() {
    FLASH_DUKR = FLASH_DUKR_KEY1;
    FLASH_DUKR = FLASH_DUKR_KEY2;
    while (!(FLASH_IAPSR & FLASH_IAPSR_DUL));
}