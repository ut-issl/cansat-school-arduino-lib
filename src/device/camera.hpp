#pragma once

#include <SPI.h>
#include <Wire.h>

#include "ArduCAM.h"

namespace Device
{

    class Camera
    {
      public:

        Camera(uint8_t ss_pin);
        ~Camera();

        void init();
        bool takePictureAndSaveAs(const String& file_name, unsigned long timeout_ms = 1000);

        void setSize(uint8_t size);

      private:

        uint8_t ss_pin_;

        ArduCAM cam_;
        uint8_t size_ = OV2640_320x240;
    };

}  // namespace Device
