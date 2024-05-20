/*
异步写例子在SCS15中测试通过，如果测试其它型号SCS系列舵机请更改合适的位置、速度与延时参数。
*/

#include <SCServo.h>

SCSCL sc;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(1000000);
  sc.pSerial = &Serial1;
  delay(1000);

  sc.RegWritePos(1, 0, 0, 800);//Servo ID1
  sc.RegWriteAction();
  delay(754);//[(P1-P0)/V]*1000+100
  sc.RegWritePos(2, 0, 0, 800);
  sc.RegWriteAction();//Servo ID2
  delay(754);//[(P1-P0)/V]*1000+100

}
void loop()
{
}
