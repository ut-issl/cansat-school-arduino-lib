#include "servo_motor.hpp"

#include "computer.hpp"

namespace Device
{

    ServoMotor::ServoMotor(const uint8_t& out_pin)
    {
        servo_.attach(out_pin);
        this->rotateTo(0);
    }

    ServoMotor::~ServoMotor()
    {
        servo_.detach();
    }

    void ServoMotor::init()
    {
        servo_.write(0);

        print(F("Init Servo Motor"));
    }

    void ServoMotor::rotateTo(int angle)
    {
        servo_.write(angle);
    }

    int ServoMotor::read() const
    {
        return servo_.read();
    }

}  // namespace Device