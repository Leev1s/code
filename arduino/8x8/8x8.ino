#include <MPU6050_tockn.h>
#include <Wire.h>
#include <LedControl.h>
MPU6050 mpu6050(Wire);
int DIN = 3;
int CS =  4;
int CLK = 5;

byte r[8]=     {0x08,0x0C,0x0E,0xFF,0xFF,0x0E,0x0C,0x08};  //➡️
byte l[8]=     {0x10,0x30,0x70,0xFF,0xFF,0x70,0x30,0x10};  //⬅️

LedControl lc=LedControl(DIN,CLK,CS,4);
void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  lc.shutdown(0,false);       //启动时，MAX72XX处于省电模式
  lc.setIntensity(0,8);       //将亮度设置为最大值
  lc.clearDisplay(0);         //清除显示
}

void loop() {
  mpu6050.update();
  float x=(mpu6050.getAngleX());
  float y=(mpu6050.getAngleY());
  float z=(mpu6050.getAngleZ());

  if(x>15)
  {printByte(r);}
  
  if(x>-5&&x<5)
  {lc.clearDisplay(0);}
  
  if(x<-15)
  {printByte(l);}
  
  Serial.print("angleX : ");
  Serial.print(mpu6050.getAngleX());
  Serial.print("\tangleY : ");
  Serial.print(mpu6050.getAngleY());
  Serial.print("\tangleZ : ");
  Serial.println(mpu6050.getAngleZ());
}

//点阵显示函数
void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}
