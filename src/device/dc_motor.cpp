#include "dc_motor.hpp"

#include "computer.hpp"

namespace Device
{

    DCMotor::DCMotor(const uint8_t& input_pin_1, const uint8_t& input_pin_2)
        : input_pin_1_{input_pin_1}, input_pin_2_{input_pin_2}
    {
    }

    DCMotor::~DCMotor()
    {
        this->free();
        pinMode(input_pin_1_, INPUT);
        pinMode(input_pin_2_, INPUT);
    }

    void DCMotor::init()
    {
        pinMode(input_pin_1_, OUTPUT);
        pinMode(input_pin_2_, OUTPUT);
        digitalWrite(input_pin_1_, LOW);
        digitalWrite(input_pin_2_, LOW);

        print(F("Init DC Motor"));
    }

    void DCMotor::free()
    {
        digitalWrite(input_pin_1_, LOW);
        digitalWrite(input_pin_2_, LOW);
    }

    void DCMotor::forward()
    {
        digitalWrite(input_pin_1_, HIGH);
        digitalWrite(input_pin_2_, LOW);
    }

    void DCMotor::reverse()
    {
        digitalWrite(input_pin_1_, LOW);
        digitalWrite(input_pin_2_, HIGH);
    }

    void DCMotor::brake()
    {
        digitalWrite(input_pin_1_, HIGH);
        digitalWrite(input_pin_2_, HIGH);
    }

}  // namespace Device