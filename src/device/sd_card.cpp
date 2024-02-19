#include "sd_card.hpp"

#include <SPI.h>
#include <Wire.h>

#include "computer.hpp"

namespace Device::SDCard
{

    void init(const uint8_t& ss_pin)
    {
        print(F("[SDCard] Initializing..."));

        pinMode(ss_pin, OUTPUT);
        if (!SD.begin(ss_pin)) {
            Computer::print(F("[SDCard] Failed to initialize"));
            while (true) {
                // do nothing
            }
        }
        Computer::print(F("[SDCard] Initialized"));
    }

    void write(const String& file_name, const String& data)
    {
        File file = SD.open(file_name, FILE_WRITE);

        if (file) {
            file.println(data);
            file.close();
        } else {
            Computer::print(F("[SDCard] Failed to open file"));
        }
        file.close();
    }

}  // namespace Device::SDCard