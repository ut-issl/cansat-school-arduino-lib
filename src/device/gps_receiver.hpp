#pragma once

#include <SoftwareSerial.h>

#include "sensor_base.hpp"

namespace Device
{

    struct GPS_t
    {
        float lat;   // [°]
        float lon;   // [°]
        float alt;   // [m]
        float time;  // [s]

        void print() const;
    };

    class GPSReceiver : public SensorBase<GPS_t>
    {
      public:

        GPSReceiver(uint8_t tx_pin);
        ~GPSReceiver() = default;

        void init();
        GPS_t read() override;
        bool isAvailable() const;

      private:

        static float ConvertNMEAToDDf_(float val);

        SoftwareSerial serial_;

        bool is_available_;
    };

}  // namespace Device
