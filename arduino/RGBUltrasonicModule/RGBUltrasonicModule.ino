







































#include <Wire.h>//导入通信库
#include <LiquidCrystal_I2C.h>  //导入LCD1602库
#include "RgbUltrasonic.h"//导入RGB超声波库

#define IOPin  6//定义TGB超声波 IO引脚
#define RGBPin 5//定义RGB超声波 RGB引脚
RgbUltrasonic mRUS04(6, 5);//创建RGB超声波对象与初始化IO引脚和RGB引脚
LiquidCrystal_I2C mylcd(0x27, 16, 2);   //初始化LCD1602
int Distance;//定义数字变量读取RGB超声波数据
void setup() {
    mylcd.init();
	mylcd.backlight();
    Serial.begin(9600);//设置串口波特率
}
void loop() {
    mRUS04.SetRgbEffect(E_RGB_ALL,0xFF0000, E_EFFECT_BREATHING);//设置RGB超声波灯颜色与数量
    mylcd.setCursor(1-1, 1-1);
	Distance = mRUS04.GetUltrasonicDistance();//获取RGB超声波所测距离
	mylcd.print("Distance is:");
	mylcd.setCursor(12-1, 1-1);
    mylcd.print(Distance);//打印RGB超声波所测距离
    mylcd.print("cm");
    delay(200);
}
