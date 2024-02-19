#pragma once

#include <Arduino.h>

namespace Device
{

    namespace Computer
    {

        template <class Last>
        void print_impl(Last last)
        {
            Serial.println(last);
        }

        template <class Head, class... Args>
        void print_impl(Head head, Args... args)
        {
            Serial.print(head);
            Serial.print(F(" "));
            print_impl(args...);
        }

        template <class... Args>
        void print(Args... args)
        {
            if (millis() < 1e4) {
                Serial.print(F("   "));
            } else if (millis() < 1e5) {
                Serial.print(F("  "));
            } else if (millis() < 1e6) {
                Serial.print(F(" "));
            }
            Serial.print(millis() / 1e3, 3);
            Serial.print(F(":  "));
            print_impl(args...);
        }

        inline void init(const unsigned long& baud_rate)
        {
            Serial.begin(baud_rate);
            while (!Serial) {
            }
            delay(1000);
            print(F("[Computer] Initialized"));
        }

    }  // namespace Computer

    using Computer::print;

}  // namespace Device
