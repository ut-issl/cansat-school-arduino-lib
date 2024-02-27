#include "sd_card.hpp"

#include <SPI.h>
#include <Wire.h>

#include "../utility/logger.hpp"

namespace Device
{

    bool SDCard::init(uint8_t ss_pin)
    {
        Utility::logger.info(F("[SDCard] Initializing..."));

        pinMode(ss_pin, OUTPUT);
        if (!SD.begin(ss_pin)) {
            Utility::logger.error(F("[SDCard] Failed to initialize"));
            return false;
        }

        Utility::logger.info(F("[SDCard] Initialized"));
        return true;
    }

}  // namespace Device