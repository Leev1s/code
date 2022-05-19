#include <IRremote.h>     // IRremote库声明
 
int RECV_PIN = 2;        
 
IRrecv irrecv(RECV_PIN); 
 
decode_results results;
int a=0;
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // 启动接收器
  pinMode(8,OUTPUT);
}
 
void loop() {
  if (irrecv.decode(&results)) 
  {
    Serial.println(results.value,HEX);//以16进制换行输出接收代码
    if(results.value==0xFF38C7 & a==0)
    {digitalWrite(8,HIGH);
    a=1;}
    else if(results.value==0xFF38C7 & a==1)
    {digitalWrite(8,LOW);
    a=0;}
    irrecv.resume(); // 接收下一个值
  }}
