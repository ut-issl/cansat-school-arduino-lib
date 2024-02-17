#pragma once

#include <SPI.h>
#include <Wire.h>

#include "ArduCAM.h"

namespace Device
{

    class Camera
    {
      public:

        Camera(const uint8_t& ss_pin);
        ~Camera();

        void init();
        bool takePictureAndSaveAs(const String& file_name);

        void setSize(uint8_t size);

      private:

        void takePicture_();
        bool savePictureToSD_(const String& file_name);

        uint8_t ss_pin_;

        ArduCAM cam_;
        uint8_t size_ = OV2640_160x120;
    };

}  // namespace Device