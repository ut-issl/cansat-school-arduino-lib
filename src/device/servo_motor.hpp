#pragma once

#include <Servo.h>

namespace Device
{

    class ServoMotor
    {
      public:

        ServoMotor(uint8_t input_pin);
        ~ServoMotor();

        void init();
        void rotateTo(int angle);  // set angle in degrees, 1 to 180
        void rotateEndless(int speed); // set speed (no units), -90 to 90
        int read() const;          // returns the current angle in degrees

      private:

        Servo servo_;
        uint8_t input_pin_;
    };


}  // namespace Device
