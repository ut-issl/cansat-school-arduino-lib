#include "sd_card.hpp"

#include <SPI.h>
#include <Wire.h>

namespace Device
{

    bool SDCard::init(uint8_t ss_pin)
    {
        Utility::print(F("[SDCard] Initializing..."));

        pinMode(ss_pin, OUTPUT);
        if (!SD.begin(ss_pin)) {
            Utility::print(F("[SDCard] Failed to initialize"));
            return false;
        }

        Utility::print(F("[SDCard] Initialized"));
        return true;
    }

}  // namespace Device