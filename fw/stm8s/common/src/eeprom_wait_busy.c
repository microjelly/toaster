#include "eeprom.h"

void eeprom_wait_busy() {
    while (!(FLASH_IAPSR & FLASH_IAPSR_EOP));
}