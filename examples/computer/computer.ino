#include <CanSatHighSchool.h>

void setup()
{
    // 通信速度9600bpsでシリアル通信を開始
    Computer::init(9600);
}

void loop()
{
    print("Hello, World!");
    delay(1000);
}
