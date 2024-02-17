#include "camera.hpp"

#include "computer.hpp"
#include "sd_card.hpp"

namespace Device
{

    Camera::Camera(const uint8_t& ss_pin)
        : ss_pin_{ss_pin}, cam_{OV2640, ss_pin}
    {
    }

    Camera::~Camera()
    {
    }

    void Camera::init()
    {
        pinMode(ss_pin_, OUTPUT);
        digitalWrite(ss_pin_, HIGH);

        // Reset the CPLD
        cam_.write_reg(0x07, 0x80);
        delay(100);
        cam_.write_reg(0x07, 0x00);
        delay(100);

        while (1) {
            // Check if the ArduCAM SPI bus is OK
            cam_.write_reg(ARDUCHIP_TEST1, 0x55);
            uint8_t temp = cam_.read_reg(ARDUCHIP_TEST1);
            if (temp != 0x55) {
                print(F("CAMERA: SPI interface Error!"));
                delay(1000);
                continue;
            } else {
                print(F("CAMERA: SPI interface OK."));
                break;
            }
        }

        while (1) {
            // Check if the camera module type is OV2640
            uint8_t vid, pid;
            cam_.wrSensorReg8_8(0xff, 0x01);
            cam_.rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
            cam_.rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
            if ((vid != 0x26) && ((pid != 0x41) || (pid != 0x42))) {
                print(F("CAMERA: ACK CMD Can't find OV2640 module!"));
                delay(1000);
                continue;
            } else {
                print(F("CAMERA: ACK CMD OV2640 detected."));
                break;
            }
        }

        // Change to JPEG capture mode and initialize the OV5640 module
        cam_.set_format(JPEG);
        cam_.InitCAM();
        cam_.clear_fifo_flag();
        cam_.write_reg(ARDUCHIP_FRAMES, 0x00);

        cam_.CS_HIGH();  // これしておかないとSDにかけない．

        print(F("Camera init done."));
    }

    bool Camera::takePictureAndSaveAs(const String& file_name)
    {
        takePicture_();

        if (!savePictureToSD_(file_name)) {
            return false;
        }

        // Clear the capture done flag
        cam_.clear_fifo_flag();

        return true;
    }

    void Camera::setSize(uint8_t size)
    {
        size_ = size;
    }

    void Camera::takePicture_()
    {
        cam_.CS_HIGH();

        cam_.CS_LOW();
        cam_.flush_fifo();
        cam_.clear_fifo_flag();
        cam_.OV2640_set_JPEG_size(size_);

        cam_.start_capture();
        print(F("CAMERA: Start Capture"));

        while (!cam_.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK)) {
        }

        print(F("CAMERA: Capture Done."));
    }

    bool Camera::savePictureToSD_(const String& file_name)
    {
        byte buf[256];

        uint32_t length = cam_.read_fifo_length();
        cam_.CS_HIGH();

        if (length >= MAX_FIFO_SIZE) {  // 8M
            print(F("CAMERA: Over size."));
            return false;
        }
        if (length == 0) {  // 0 kb
            print(F("CAMERA: Size is 0."));
            return false;
        }

        cam_.CS_LOW();
        cam_.set_fifo_burst();  // Set fifo burst mode

        int i = 0;
        bool is_header = false;
        File output_file;
        uint8_t temp = 0, temp_last = 0;
        while (length--) {
            temp_last = temp;
            temp = SPI.transfer(0x00);
            // Read JPEG data from FIFO
            if ((temp == 0xD9) && (temp_last == 0xFF)) {  // If find the end ,break while,
                buf[i++] = temp;                          // save the last  0XD9
                // Write the remain bytes in the buffer
                cam_.CS_HIGH();
                output_file.write(buf, i);
                // Close the file
                output_file.close();
                print(F("CAMERA: Save OK"));
                is_header = false;
                cam_.CS_LOW();
                cam_.set_fifo_burst();
                i = 0;
            }
            if (is_header == true) {
                // Write image data to buffer if not full
                if (i < 256) {
                    buf[i++] = temp;
                } else {
                    // Write 256 bytes image data to file
                    cam_.CS_HIGH();
                    output_file.write(buf, 256);
                    i = 0;
                    buf[i++] = temp;
                    cam_.CS_LOW();
                    cam_.set_fifo_burst();
                }
            } else if ((temp == 0xD8) & (temp_last == 0xFF)) {
                print(F("CAMERA: HEADER FOUND!!!"));
                is_header = true;

                cam_.CS_HIGH();

                output_file = SD.open(file_name, O_WRITE | O_CREAT | O_TRUNC);
                if (!output_file) {
                    print(F("SD: File open failed"));
                }
                cam_.CS_LOW();
                cam_.set_fifo_burst();
                buf[i++] = temp_last;
                buf[i++] = temp;
            }
        }

        cam_.CS_HIGH();
        return true;
    }


}  // namespace Device
