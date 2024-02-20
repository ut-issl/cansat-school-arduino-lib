#pragma once

#include <Arduino.h>

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

        void info(const String& message) const;
        void error(const String& message) const;
        void warning(const String& message) const;
        void debug(const String& message) const;

      private:

        String timestamp_() const;

        bool is_debug_ = false;

        bool use_computer_ = false;
        bool use_sd_card_ = false;

        String log_file_name_;
    };

    extern Logger logger;

}  // namespace Utility
