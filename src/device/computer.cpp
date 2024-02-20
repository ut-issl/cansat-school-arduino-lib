#include "computer.hpp"

#include "../utility/logger.hpp"

namespace Device
{

    bool Computer::init(const unsigned long& baud_rate = 9600, const unsigned long& timeout_ms = 10000)
    {
        Serial.begin(baud_rate);
        unsigned long start = millis();
        while (!Serial) {
            if (millis() - start > timeout_ms) {
                return false;
            }
        }
        delay(1000);
        Utility::logger.info(F("[Computer] Initialized"));
        return true;
    }

}  // namespace Device
