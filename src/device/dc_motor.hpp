#pragma once

#include <Servo.h>

namespace Device
{

    class DCMotor
    {
      public:

        DCMotor(const uint8_t& input_pin_1, const uint8_t& input_pin_2);
        ~DCMotor();

        void init();

        void free();
        void forward();
        void reverse();
        void brake();

      private:

        uint8_t input_pin_1_;
        uint8_t input_pin_2_;
    };

}  // namespace Device
