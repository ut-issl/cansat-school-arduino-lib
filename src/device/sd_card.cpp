#include "sd_card.hpp"

#include <SPI.h>
#include <Wire.h>

#include "computer.hpp"

namespace Device
{

    bool SDCard::init(uint8_t ss_pin)
    {
        print(F("[SDCard] Initializing..."));

        pinMode(ss_pin, OUTPUT);
        if (!SD.begin(ss_pin)) {
            print(F("[SDCard] Failed to initialize"));
            return false;
        }

        print(F("[SDCard] Initialized"));
        return true;
    }

}  // namespace Device