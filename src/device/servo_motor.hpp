#pragma once

#include <Servo.h>

namespace Device
{

    class ServoMotor
    {
      public:

        ServoMotor(const uint8_t& out_pin);
        ~ServoMotor();

        void init();
        void rotateTo(int angle);  // set angle in degrees, 0 to 180
        int read() const;          // returns the current angle in degrees

      private:

        Servo servo_;
    };


}  // namespace Device
