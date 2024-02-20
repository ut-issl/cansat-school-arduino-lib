#include "logger.hpp"

#include "../device/computer.hpp"
#include "../device/sd_card.hpp"
#include "printer.hpp"

namespace Utility
{

    void Logger::setDebug(const bool& is_debug)
    {
        is_debug_ = is_debug;
    }

    bool Logger::enableComputer(const unsigned long& baud_rate)
    {
        Device::Computer::init(baud_rate);
        use_computer_ = true;
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

    void Logger::info(const String& message) const
    {
        if (use_computer_) {
            print(timestamp_(), F("[INFO]"), message);
        }
        if (use_sd_card_) {
            Device::SDCard::write(log_file_name_, timestamp_() + F(" [INFO] ") + message);
        }
    }

    void Logger::error(const String& message) const
    {
        if (use_computer_) {
            print(timestamp_(), F("[ERROR]"), message);
        }
        if (use_sd_card_) {
            Device::SDCard::write(log_file_name_, timestamp_() + F(" [ERROR] ") + message);
        }
    }

    void Logger::warning(const String& message) const
    {
        if (use_computer_) {
            print(timestamp_(), F("[WARNING]"), message);
        }
        if (use_sd_card_) {
            Device::SDCard::write(log_file_name_, timestamp_() + F(" [WARNING] ") + message);
        }
    }

    void Logger::debug(const String& message) const
    {
        if (is_debug_) {
            if (use_computer_) {
                print(timestamp_(), F("[DEBUG]"), message);
            }
            if (use_sd_card_) {
                Device::SDCard::write(log_file_name_, timestamp_() + F(" [DEBUG] ") + message);
            }
        }
    }

    String Logger::timestamp_() const
    {
        double sec = float(millis()) / 1000.0;
        char buffer[9];
        dtostrf(sec, 7, 2, buffer);
        return String(buffer);
    }

    Logger logger;

}  // namespace Utility