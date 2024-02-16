#include "gps_receiver.hpp"

#include "computer.hpp"

namespace Device
{

    void GPS_t::print() const
    {
        Computer::print(F("Time:"), time, F("Latitude:"), lat, F("Longitude:"), lon, F("Height:"), height);
    }

    GPSReceiver::GPSReceiver(const uint8_t& tx_pin, const uint8_t& rx_pin)
        : serial_{tx_pin, rx_pin}, is_available_{false}
    {
    }

    void GPSReceiver::init()
    {
        serial_.begin(9600);
        while (!serial_) {
        }
        delay(1000);
        print(F("Init GPS Receiver"));
    }

    GPS_t GPSReceiver::read()
    {
        GPS_t gps;
        String line = serial_.readStringUntil('\n');
        if (line != "") {
            uint16_t i;
            uint8_t index = 0;
            uint16_t len = line.length();
            String str = "";

            const uint8_t MAX_LIST = 12;
            String list[MAX_LIST];
            for (i = 0; i < MAX_LIST; i++) {
                list[i] = "";
            }

            for (i = 0; i < len; i++) {
                if (index >= MAX_LIST) {
                    break;
                }
                if (line[i] == ',') {
                    list[index++] = str;
                    str = "";
                    continue;
                }
                str += line[i];
            }

            if (list[0] == "$GPGGA") {
                if (list[6] != "0") {
                    gps.time = millis() / 1000;
                    gps.lat = ConvertNMEAToDDf_(list[2].toFloat());
                    gps.lon = ConvertNMEAToDDf_(list[4].toFloat());
                    gps.height = list[9].toFloat();
                    is_available_ = true;
                } else {
                    is_available_ = false;
                }
            }
        }
        return gps;
    }

    bool GPSReceiver::isAvailable() const
    {
        return is_available_;
    }

    float GPSReceiver::ConvertNMEAToDDf_(float val)
    {
        int deg = val / 100;
        float min = val - deg * 100;
        return deg + min / 60.0;
    }

}  // namespace Device
