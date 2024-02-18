#include "servo_motor.hpp"

#include "computer.hpp"

namespace Device
{

    ServoMotor::ServoMotor(const uint8_t& input_pin)
        : input_pin_(input_pin)
    {
    }

    ServoMotor::~ServoMotor()
    {
        servo_.detach();
    }

    void ServoMotor::init()
    {
        servo_.attach(input_pin_);
        delay(1000);
        this->rotateTo(1);

        print(F("Init Servo Motor"));
    }

    void ServoMotor::rotateTo(int angle)
    {
        if (angle < 1) {
            angle = 1;
        }
        if (angle > 180) {
            angle = 180;
        }
        servo_.write(angle);
    }

    int ServoMotor::read() const
    {
        return servo_.read();
    }

}  // namespace Device