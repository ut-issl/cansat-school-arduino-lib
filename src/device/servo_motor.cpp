#include "servo_motor.hpp"

#include "../utility/logger.hpp"

namespace Device
{

    ServoMotor::ServoMotor(uint8_t input_pin)
        : input_pin_(input_pin)
    {
    }

    ServoMotor::~ServoMotor()
    {
        servo_.detach();
    }

    void ServoMotor::init()
    {
        Utility::logger.info(F("[ServoMotor] Initializing..."));

        servo_.attach(input_pin_);
        delay(1000);
        this->rotateTo(1);

        Utility::logger.info(F("[ServoMotor] Initialized"));
    }

    void ServoMotor::rotateTo(int angle)
    {
        if (angle < 1) {
            Utility::logger.warning(F("[ServoMotor] Desired angle"), angle, F("[deg] is less than 1. Set to 1"));
            angle = 1;
        }
        if (angle > 180) {
            Utility::logger.warning(F("[ServoMotor] Desired angle"), angle, F("[deg] is greater than 180. Set to 180"));
            angle = 180;
        }
        servo_.write(angle);
    }

    void ServoMotor::rotateEndless(int speed)
    {
        servo_.write(speed - 90);
    }

    int ServoMotor::read() const
    {
        return servo_.read();
    }

}  // namespace Device