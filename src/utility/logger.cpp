#include "logger.hpp"

#include "../device/computer.hpp"

namespace Utility
{

    void Logger::setDebug(const bool& is_debug)
    {
        is_debug_ = is_debug;
    }

    bool Logger::enableComputer(const unsigned long& baud_rate)
    {
        use_computer_ = true;
        if (!Device::Computer::init(baud_rate)) {
            use_computer_ = false;
            return false;
        }
        return true;
    }

    bool Logger::enableSDCard(const String& log_file_name, uint8_t ss_pin)
    {
        if (!Device::SDCard::init(ss_pin)) {
            return false;
        }
        log_file_name_ = log_file_name;
        use_sd_card_ = true;
        return true;
    }

    String Logger::timestamp_() const
    {
        float sec = float(millis()) / 1000.0;
        char buffer[9];
        dtostrf(sec, 7, 2, buffer);
        return String(buffer);
    }

    Logger logger;

}  // namespace Utility