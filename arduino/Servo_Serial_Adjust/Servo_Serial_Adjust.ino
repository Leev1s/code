#include <Servo.h>

Servo servo1;

Servo servo2;

void setup() 
{
    servo1.attach(13); //设置舵机信号引脚
    servo2.attach(4);
}

void loop()  
{
	servo1.write(170); //设置舵机需要转的角度
	delay(2000);
	servo2.write(180); //设置舵机需要转的角度
	delay(2000);
  servo1.write(10); //设置舵机需要转的角度
  delay(2000);
  servo2.write(0); //设置舵机需要转的角度
  delay(2000);
}
