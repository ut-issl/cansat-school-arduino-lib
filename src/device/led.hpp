#pragma once

#include <Arduino.h>

namespace Device
{

    class Led
    {
      public:

        Led(uint8_t output_pin);
        ~Led() = default;

        void init();
        void on();
        void off();
        void blink(uint16_t duration_ms);

      private:

        uint8_t output_pin_;
    };

}  // namespace Device
