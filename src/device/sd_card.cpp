#include "sd_card.hpp"

#include <SPI.h>
#include <Wire.h>

#include "computer.hpp"

namespace Device::SDCard
{

    bool init(uint8_t ss_pin)
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

    bool write(const String& file_name, const String& data)
    {
        File file = SD.open(file_name, FILE_WRITE);
        if (!file) {
            print(F("[SDCard] Failed to open file"));
            return false;
        }
        file.println(data);
        file.close();
        return true;
    }

}  // namespace Device::SDCard