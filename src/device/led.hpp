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

      private:

        uint8_t output_pin_;
    };

}  // namespace Device
