#include "led.hpp"

#include "../utility/logger.hpp"

namespace Device
{

    Led::Led(uint8_t output_pin)
        : output_pin_(output_pin)
    {
    }

    void Led::init()
    {
        Utility::logger.info(F("[LED] Initialized"));
    }

    void Led::on()
    {
        digitalWrite(output_pin_, HIGH);
        Utility::logger.info(F("[LED] ON"));
    }

    void Led::off()
    {
        digitalWrite(output_pin_, LOW);
        Utility::logger.info(F("[LED] OFF"));
    }


}  // namespace Device
