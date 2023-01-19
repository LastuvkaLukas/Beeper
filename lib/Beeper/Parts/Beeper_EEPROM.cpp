#include "Beeper_EEPROM.h"

/// @brief EEPROM initialize
void eeprom_begin()
{
    if (!EEPROM.begin(1))
    {
        Serial.println(F("EEPROM failed to initialise"));
    }
}

/// @brief Update byte on default address on EEPROM
/// @param byte Byte to write
void eeprom_write(uint8_t byte)
{
    if (eeprom_read() == byte)
        return;

    EEPROM.writeByte(EEPROM_START_ADDR, byte);
    EEPROM.commit();
}

/// @brief Read byte from default address from EEPROM
/// @return Read byte
uint8_t eeprom_read()
{
    return EEPROM.readByte(EEPROM_START_ADDR);
}

//* -------------------------------
//* END
