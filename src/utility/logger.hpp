#pragma once

#include "../device/sd_card.hpp"
#include "printer.hpp"

namespace Utility
{

    class Logger
    {
      public:

        Logger() = default;
        ~Logger() = default;

        void setDebug(const bool& is_debug = true);

        bool enableComputer(const unsigned long& baud_rate = 9600);
        bool enableSDCard(const String& log_file_name = "log.txt", uint8_t ss_pin = 10);

        template <class... Args>
        void info(Args... messages) const;
        template <class... Args>
        void error(Args... messages) const;
        template <class... Args>
        void warning(Args... messages) const;
        template <class... Args>
        void debug(Args... messages) const;

      private:

        String timestamp_() const;

        bool is_debug_ = false;

        bool use_computer_ = false;
        bool use_sd_card_ = false;

        String log_file_name_;
    };

    template <class... Args>
    inline void Logger::info(Args... messages) const
    {
        if (use_computer_) {
            print(timestamp_(), F("[INFO]"), messages...);
        }
        if (use_sd_card_) {
            Device::SDCard::write(log_file_name_, timestamp_(), F("[INFO]"), messages...);
        }
    }

    template <class... Args>
    inline void Logger::error(Args... messages) const
    {
        if (use_computer_) {
            print(timestamp_(), F("[ERROR]"), messages...);
        }
        if (use_sd_card_) {
            Device::SDCard::write(log_file_name_, timestamp_(), F("[ERROR]"), messages...);
        }
    }

    template <class... Args>
    inline void Logger::warning(Args... messages) const
    {
        if (use_computer_) {
            print(timestamp_(), F("[WARNING]"), messages...);
        }
        if (use_sd_card_) {
            Device::SDCard::write(log_file_name_, timestamp_(), F("[WARNING]"), messages...);
        }
    }

    template <class... Args>
    inline void Logger::debug(Args... messages) const
    {
        if (is_debug_) {
            if (use_computer_) {
                print(timestamp_(), F("[DEBUG]"), messages...);
            }
            if (use_sd_card_) {
                Device::SDCard::write(log_file_name_, timestamp_(), F("[DEBUG]"), messages...);
            }
        }
    }

    extern Logger logger;

}  // namespace Utility
