#include "DHT.h"
#include <Wire.h>
#include "LiquidCrystal_I2C.h"
#define DHTPIN 8    // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 3 (on the right) of the sensor to GROUND (if your sensor has 3 pins)
// Connect pin 4 (on the right) of the sensor to GROUND and leave the pin 3 EMPTY (if your sensor has 4 pins)
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);
int i=0;
void setup() {
  Serial.begin(9600);
  pinMode(7,INPUT);
  pinMode(10,OUTPUT);
  lcd.init();
  lcd.backlight();
  dht.begin();
  digitalWrite(10,LOW);
}

void loop() {
  // Wait a few seconds between measurements.
delay(500);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);


  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    lcd.init();
    lcd.setCursor(5,0);
    lcd.print(F("Failed"));
    return;
  }
  if(digitalRead(7)==HIGH)
  {if(digitalRead(7)==HIGH)
  {digitalWrite(10,HIGH);
   i=i+1;
   delay(500);}
   digitalWrite(10,LOW);}
   
  lcd.setCursor(0,0);
  lcd.print(F("Hum: "));
  lcd.print(h,1);
  lcd.print(F("% "));
  lcd.setCursor(0,1);
  lcd.print("Tem: ");
  lcd.print(t,1);
  lcd.print(F("'C "));
  lcd.print("");
  lcd.print(i);
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  
   
}
