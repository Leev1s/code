#define RGB_RED   9
#define RGB_GREEN 10
#define RGB_BLUE  11

void setup()
{
  pinMode(RGB_RED, OUTPUT);
  pinMode(RGB_GREEN, OUTPUT);
  pinMode(RGB_BLUE, OUTPUT);
}
void loop()
{
  int i;//RGB数值
  int t=2;//速度
  for(i=255;i>1;i--)
  {analogWrite(RGB_RED,i);
   analogWrite(RGB_GREEN,255);
   analogWrite(RGB_BLUE,1);
   delay(t);}
   for(i=1;i<255;i++)
  {analogWrite(RGB_RED,1);
   analogWrite(RGB_GREEN,255);
   analogWrite(RGB_BLUE,i);
   delay(t);}
   for(i=255;i>1;i--)
  {analogWrite(RGB_RED,1);
   analogWrite(RGB_GREEN,i);
   analogWrite(RGB_BLUE,255);
   delay(t);}
   for(i=1;i<255;i++)
  {analogWrite(RGB_RED,i);
   analogWrite(RGB_GREEN,1);
   analogWrite(RGB_BLUE,255);
   delay(t);}
   for(i=255;i>1;i--)
  {analogWrite(RGB_RED,255);
   analogWrite(RGB_GREEN,1);
   analogWrite(RGB_BLUE,i);
   delay(t);}
   for(i=1;i<255;i++)
  {analogWrite(RGB_RED,255);
   analogWrite(RGB_GREEN,i);
   analogWrite(RGB_BLUE,1);
   delay(1);}
     
}
