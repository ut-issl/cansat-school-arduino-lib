#include "camera.hpp"

#include "../utility/logger.hpp"
#include "sd_card.hpp"

namespace Device
{

    Camera::Camera(uint8_t ss_pin)
        : ss_pin_{ss_pin}, cam_{OV2640, ss_pin}
    {
    }

    Camera::~Camera()
    {
        digitalWrite(ss_pin_, LOW);
    }

    void Camera::init(unsigned long timeout_ms)
    {
        Utility::logger.info(F("[Camera] Initializing..."));

        pinMode(ss_pin_, OUTPUT);
        digitalWrite(ss_pin_, HIGH);

        // Reset the CPLD
        cam_.write_reg(0x07, 0x80);
        delay(100);
        cam_.write_reg(0x07, 0x00);
        delay(100);

        unsigned long start_time = millis();
        while (millis() - start_time < timeout_ms) {
            // Check if the ArduCAM SPI bus is OK
            cam_.write_reg(ARDUCHIP_TEST1, 0x55);
            uint8_t temp = cam_.read_reg(ARDUCHIP_TEST1);
            if (temp != 0x55) {
                Utility::logger.error(F("[Camera] SPI interface error"));
            } else {
                Utility::logger.debug(F("[Camera] SPI interface OK"));
                break;
            }
            delay(1000);
        }

        start_time = millis();
        while (millis() - start_time < timeout_ms) {
            // Check if the camera module type is OV2640
            uint8_t vid, pid;
            cam_.wrSensorReg8_8(0xff, 0x01);
            cam_.rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
            cam_.rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
            if ((vid != 0x26) && ((pid != 0x41) || (pid != 0x42))) {
                Utility::logger.error(F("[Camera] Cannot find camera module"));
            } else {
                Utility::logger.debug(F("[Camera] Camera module detected"));
                is_available_ = true;
                break;
            }
            delay(1000);
        }

        // Change to JPEG capture mode and initialize the OV5640 module
        cam_.set_format(JPEG);
        cam_.InitCAM();
        cam_.clear_fifo_flag();
        cam_.write_reg(ARDUCHIP_FRAMES, 0x00);

        cam_.CS_HIGH();  // これしておかないとSDにかけない

        if (is_available_) {
            Utility::logger.info(F("[Camera] Initialized"));
        } else {
            Utility::logger.error(F("[Camera] Failed to initialize"));
        }
    }

    bool Camera::takePictureAndSaveAs(const String& file_name, unsigned long timeout_ms)
    {
        if (!is_available_) {
            Utility::logger.warning(F("[Camera] Camera is not available, skipping taking picture"));
            return false;
        }

        char str[8];
        byte buf[256];
        static int i = 0;
        static int k = 0;
        uint8_t temp = 0, temp_last = 0;
        uint32_t length = 0;
        bool is_header = false;
        File outFile;
        // Flush the FIFO
        cam_.flush_fifo();
        // Clear the capture done flag
        cam_.clear_fifo_flag();
        cam_.OV2640_set_JPEG_size(size_);

        // Capture
        unsigned long start_time = millis();
        cam_.start_capture();
        Utility::logger.info(F("[Camera] Start capture"));
        while (!cam_.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK)) {
            if ((millis() - start_time) > timeout_ms) {
                Utility::logger.error(F("[Camera] Capture timeout"));
                return false;
            }
        }
        Utility::logger.info(F("[Camera] Capture done"));

        length = cam_.read_fifo_length();
        if (length >= MAX_FIFO_SIZE)  // 384K
        {
            Utility::logger.error(F("[Camera] Image size is too large"));
            return false;
        }
        if (length == 0)  // 0 kb
        {
            Utility::logger.error(F("[Camera] Image size is 0"));
            return false;
        }

        // Save the image to SD card
        outFile = SD.open(file_name.c_str(), O_WRITE | O_CREAT | O_TRUNC);
        if (!outFile) {
            Utility::logger.error(F("[Camera] Failed to open file"), file_name);
            return false;
        }
        cam_.CS_LOW();
        cam_.set_fifo_burst();
        while (length--) {
            temp_last = temp;
            temp = SPI.transfer(0x00);
            // Read JPEG data from FIFO
            if ((temp == 0xD9) && (temp_last == 0xFF))  // If find the end ,break while,
            {
                buf[i++] = temp;  // save the last  0XD9
                // Write the remain bytes in the buffer
                cam_.CS_HIGH();
                outFile.write(buf, i);
                // Close the file
                outFile.close();
                Utility::logger.info(F("[Camera] Image saved as"), file_name);
                is_header = false;
                i = 0;
            }
            if (is_header == true) {
                // Write image data to buffer if not full
                if (i < 256)
                    buf[i++] = temp;
                else {
                    // Write 256 bytes image data to file
                    cam_.CS_HIGH();
                    outFile.write(buf, 256);
                    i = 0;
                    buf[i++] = temp;
                    cam_.CS_LOW();
                    cam_.set_fifo_burst();
                }
            } else if ((temp == 0xD8) & (temp_last == 0xFF)) {
                is_header = true;
                buf[i++] = temp_last;
                buf[i++] = temp;
            }
        }

        return true;
    }

    void Camera::setSize(uint8_t size)
    {
        size_ = size;
    }

}  // namespace Device
