#pragma once

#include "../device/computer.hpp"
#include "../device/sd_card.hpp"

namespace Utility
{

    class Logger
    {
      public:

        Logger() = default;
        ~Logger() = default;

        void init();

        void info(const String& message) const;
        void error(const String& message) const;
        void warning(const String& message) const;
        void debug(const String& message) const;

      private:

        bool use_computer_ = true;
        bool use_sd_card_ = false;

        String log_file_name_;
    };

}  // namespace Utility
