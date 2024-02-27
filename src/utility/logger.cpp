#include "logger.hpp"

#include "../device/computer.hpp"

namespace Utility
{

    void Logger::setDebug(const bool& is_debug)
    {
        is_debug_ = is_debug;
        this->info(F("[Logger] Debug mode is"), is_debug_ ? F("enabled.") : F("disabled."));
    }

    bool Logger::enableComputer(const unsigned long& baud_rate)
    {
        use_computer_ = true;
        if (!Device::Computer::init(baud_rate)) {
            use_computer_ = false;
            return false;
        }
        this->info(F("[Logger] Start logging to computer"));
        return true;
    }

    bool Logger::enableSDCard(const String& log_file_name, uint8_t ss_pin)
    {
        if (!Device::SDCard::init(ss_pin)) {
            this->warning(F("[Logger] Logging to SD card is disabled"));
            return false;
        }
        log_file_name_ = log_file_name;
        use_sd_card_ = true;
        Device::SDCard::write(log_file_name_, F("============================================================"));
        this->info(F("[Logger] Start logging to"), log_file_name_, F("on SD card"));
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