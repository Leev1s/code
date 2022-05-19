#include "TimerOne.h"
#include "TM1637.h"
#define ON 1
#define OFF 0
int8_t TimeDisp[] = {0x00,0x00,0x00,0x00};
unsigned char ClockPoint = 1;
unsigned char Update;
unsigned char halfsecond = 0;
unsigned char second;
unsigned char minute = 48;
unsigned char hour = 11;
#define CLK A5//TM1637的引脚定义，可以更改为其他端口
#define DIO A4
TM1637 tm1637(CLK,DIO);
void setup()
{
  tm1637.set();
  tm1637.init();
  Timer1.initialize(500000);//定时500ms
  Timer1.attachInterrupt(TimingISR);//声明中断函数,定时ISR
}
void loop()
{
  if(Update == ON)
  {
    TimeUpdate();
    tm1637.display(TimeDisp);//显示时间
  }
}

void TimingISR()//计算时间
{
  halfsecond ++;
  Update = ON;
  if(halfsecond == 2){
    second ++;
    if(second == 60)
    {
      minute ++;
      if(minute == 60)
      {
        hour ++;
        if(hour == 24)
        hour = 0;
        minute = 0;
      }
      second = 0;
    }
    halfsecond = 0;  
  }
  ClockPoint = (~ClockPoint) & 0x01;
}

void TimeUpdate(void) 
{
  if(ClockPoint)tm1637.point(POINT_ON);
  else tm1637.point(POINT_OFF); 
  TimeDisp[0] = hour / 10;//取小时 十位的模
  TimeDisp[1] = hour % 10;//取小时 个位的余数
  TimeDisp[2] = minute / 10;//取分 十位的模
  TimeDisp[3] = minute % 10;//取分 个位的余数
  Update = OFF;
}
