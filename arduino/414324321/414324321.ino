const int tx = 1;
const int rx = 0;
void setup() {
  //Serial.begin(9600); 注意！！千万别加这行代码
  pinMode(rx,INPUT_PULLUP);
  pinMode(tx,INPUT_PULLUP); 

}

void loop() {

}
