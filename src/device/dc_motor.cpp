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
        print(F("[DCMotor] Initializing..."));

        pinMode(input_pin_1_, OUTPUT);
        pinMode(input_pin_2_, OUTPUT);
        digitalWrite(input_pin_1_, LOW);
        digitalWrite(input_pin_2_, LOW);

        print(F("[DCMotor] Initialized"));
    }

    void DCMotor::free()
    {
        digitalWrite(input_pin_1_, LOW);
        digitalWrite(input_pin_2_, LOW);
        print(F("[DCMotor] Free"));
    }

    void DCMotor::forward()
    {
        digitalWrite(input_pin_1_, HIGH);
        digitalWrite(input_pin_2_, LOW);
        print(F("[DCMotor] Forward"));
    }

    void DCMotor::reverse()
    {
        digitalWrite(input_pin_1_, LOW);
        digitalWrite(input_pin_2_, HIGH);
        print(F("[DCMotor] Reverse"));
    }

    void DCMotor::brake()
    {
        digitalWrite(input_pin_1_, HIGH);
        digitalWrite(input_pin_2_, HIGH);
        print(F("[DCMotor] Brake"));
    }

}  // namespace Device