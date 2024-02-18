#include <CanSatSchool.h>

#define PIN_CAMERA_SS 7
#define PIN_SD_SS 10

Camera camera{PIN_CAMERA_SS};

void setup()
{
    Computer::init(9600);

    // Wire(Arduino-I2C)の初期化
    Wire.begin();
    // SPIの初期化
    SPI.begin();

    // SDカードの初期化
    SDCard::init(PIN_SD_SS);

    camera.init();

    delay(300);
}

void loop()
{
    camera.takePictureAndSaveAs(String(millis()) + ".jpg");
    delay(10000);
}
