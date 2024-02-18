#include <CanSatSchool.h>

void setup()
{
    // シリアル通信 (Arduino-PC) を初期化
    // 9600bps で通信を開始
    Computer::init(9600);

    delay(500);
}

void loop()
{
    // シリアルモニタに "Hello, World!" と表示
    print("Hello, World!");

    // 1s 待つ
    delay(1000);
}
