#include <CanSatSchool.h>

#define PIN_SD_SS 10

String file_name = "log.txt";

void setup()
{
    Computer::init(9600);

    // SDカードの初期化
    SDCard::init(PIN_SD_SS);

    delay(300);
}

void loop()
{
    SDCard::write(file_name, String(millis()));
    delay(1000);
}
