#pragma once

#include <Arduino.h>

namespace Device
{

    namespace Computer
    {

        inline void init(const unsigned long& baud_rate = 9600)
        {
            Serial.begin(baud_rate);
            while (!Serial) {
            }
            delay(1000);
            // print(F("[Computer] Initialized"));
        }

    }  // namespace Computer

}  // namespace Device
