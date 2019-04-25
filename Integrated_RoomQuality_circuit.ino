#include <DHT.h>
#include <DHT_U.h>
#include "Air_Quality_Sensor.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

//Analog Pin
AirQualitySensor sensor(A0);  // A0
#define PIN_SMELL_OUTPUT 1    // A1
#define PIN_SOUND_CENSOR 2    // A2
#define PIN_PHOTO_CENSOR 3    // A3

//Digital Pin
#define PIN_LED_OUT 9         // D9
#define PIN_DHT 11            // D11
#define PIN_HEATER 12         // D12
#define PIN_SENSOR 13         // D13

//LEDの数
int numPixels   = 3; // Popular NeoPixel ring size
int pixelFormat = NEO_GRB + NEO_KHZ800;
Adafruit_NeoPixel *pixels;

//温湿度センサ
DHT dht(PIN_DHT,DHT11);


void setup(void) {
  Serial.begin(9600);
  
  //　　Air Quality Censor
  while (!Serial);
  Serial.println("Waiting sensor to init...");
  delay(10000);

  if (sensor.init()) {
    Serial.println("Air Sensor ready.");
  }else {
    Serial.println("Sensor ERROR!");
  }
  
  //  においセンサ
  pinMode(PIN_HEATER,OUTPUT);
  pinMode(PIN_SENSOR,OUTPUT);
  digitalWrite(PIN_HEATER,HIGH); // Heater Off
  digitalWrite(PIN_SENSOR,LOW); // Sensor Pullup Offdelay(5000);
  Serial.begin(9600);

  //温湿度センサ
  dht.begin(); 
  
  if (sensor.init()) {
    Serial.println("Sensor ready.");
  }else {
    Serial.println("Sensor ERROR!");
  }

  //LED
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  // Then create a new NeoPixel object dynamically with these values:
  pixels = new Adafruit_NeoPixel(numPixels, PIN_LED_OUT, pixelFormat);
  pixels->begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop(void) {
  pixels->clear(); // Set all pixel colors to 'off'

  
  pixels->clear(); // Set all pixel colors to 'off'
  int quality = sensor.slope();
  int smell_val=0;
  int photo_val = 0;
  int sound_val = 0;
  int minLux = 800;
  int maxLux = 430;
  int i;
  float Lux = 0;
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  Serial.println("---------------------------------------------");


  //温湿度センサのプログラム
  Serial.print("Humidity:  ");
  Serial.print(humidity);
  Serial.println("%\t");
  Serial.print("Temperature:  ");
  Serial.print(temperature);
  Serial.println(" ℃");

  //  においセンサのプログラム
  delay(237);
  digitalWrite(PIN_SENSOR,HIGH); // Sensor Pullup On
  delay(3);
  smell_val = analogRead(PIN_SMELL_OUTPUT)*2; // Get Sensor Voltage
  delay(2);
  digitalWrite(PIN_SENSOR,LOW); // Sensor Pullup Off

  digitalWrite(PIN_HEATER,LOW); // Heater On
  delay(8);
  digitalWrite(PIN_HEATER,HIGH); // Heater Off
  Serial.print("smell: ");
  Serial.println(smell_val);
  
  
  //光センサのプログラム
  photo_val = analogRead(PIN_PHOTO_CENSOR);
  Lux = 725 - (photo_val- maxLux)*5.5;    
  Serial.print("Lux:  ");
  Serial.println(Lux);
  
  //  マイクのプログラム
  sound_val = 0;
  sound_val = analogRead(PIN_SOUND_CENSOR);
  Serial.print("sound:  ");
  Serial.println(sound_val);

  //  Air Quality Censorのプログラム
  //  LED点灯の制御プログラム

  Serial.print("Sensor value: ");
  Serial.println(sensor.getValue());
  pixels->clear(); // Set all pixel colors to 'off'

  if (quality == AirQualitySensor::FORCE_SIGNAL) {
    Serial.println("__ __ __ __ __ __ __ __ __ __ __ __ __ __");
    Serial.println("| High pollution!!!! Force signal active.|");
    Serial.println(" ￣ ￣ ￣ ￣ ￣ ￣ ￣ ￣ ￣ ￣ ￣ ￣ ￣ ￣ ￣");
    for(i=0; i<100; i++){
      if(i%2==0){
        pixels->setPixelColor(0, pixels->Color(0, 50, 0));
        pixels->setPixelColor(1, pixels->Color(0, 10, 0));
        pixels->setPixelColor(2, pixels->Color(0, 50, 0));
        pixels->show();
      }else{
        pixels->setPixelColor(0, pixels->Color(0, 10, 0));
        pixels->setPixelColor(1, pixels->Color(0, 50, 0));
        pixels->setPixelColor(2, pixels->Color(0, 10, 0));
        pixels->show();
      }
      delay(100);
    }
  }else if (quality == AirQualitySensor::HIGH_POLLUTION) {
    Serial.println("__ __ __ __ __ __ __");
    Serial.println("| High pollution!!!! |");
    Serial.println("￣ ￣ ￣ ￣ ￣ ￣ ￣ ￣");
    for(i=0; i<100; i++){
      if(i%2==0){
        pixels->setPixelColor(0, pixels->Color(0, 50, 0));
        pixels->setPixelColor(1, pixels->Color(0, 10, 0));
        pixels->show();
      }else{
        pixels->setPixelColor(0, pixels->Color(0, 10, 0));
        pixels->setPixelColor(1, pixels->Color(0, 50, 0));
        pixels->show();
      }
      delay(100);
  }
  }else if (quality == AirQualitySensor::LOW_POLLUTION) {
    Serial.println("__ __ __ __ __ __");
    Serial.println("| Low pollution! |");
    Serial.println(" ￣ ￣ ￣ ￣ ￣ ￣ ");
    for(i=0; i<100; i++){
      if(i%2==0){
        pixels->setPixelColor(0, pixels->Color(30, 30, 0));
        pixels->setPixelColor(1, pixels->Color(10, 10, 0));
        pixels->show();
      }else{
        pixels->setPixelColor(0, pixels->Color(10, 10, 0));
        pixels->setPixelColor(1, pixels->Color(30, 30, 0));
        pixels->show();
      }
      delay(100);
  }
  }else if (quality == AirQualitySensor::FRESH_AIR) {
    Serial.println(" __ __ __ __");
    Serial.println("| Fresh air.|");
    Serial.println(" ￣ ￣ ￣ ￣");
    //humidity temperature
    if(humidity>85||humidity<15||temperature>30||temperature<22){
      pixels->setPixelColor(2, pixels->Color(0, 30, 0));
      pixels->show();
    }else if(humidity>70||humidity<30||temperature>26||temperature<24){
      pixels->setPixelColor(2, pixels->Color(30, 30, 0));
      pixels->show();
    }else {
      pixels->setPixelColor(2, pixels->Color(10, 0, 10));
      pixels->show();
    }
  //Lux:700 sound_val:600
  if(Lux<200){
      pixels->setPixelColor(1, pixels->Color(0, 30, 0));
      pixels->show();
  }else if(Lux<500){
      pixels->setPixelColor(1, pixels->Color(30, 30, 0));
      pixels->show();
  }else{
      pixels->setPixelColor(1, pixels->Color(10, 0, 10));
      pixels->show();
  }

  //smell_val 平常時600
  if(smell_val<350){
      pixels->setPixelColor(0, pixels->Color(0, 30, 0));
      pixels->show();
  }else if(smell_val<6yuh00){
      pixels->setPixelColor(0, pixels->Color(30, 30, 0));
      pixels->show();
  }else{
      pixels->setPixelColor(0, pixels->Color(10, 0, 10));
      pixels->show();
  }
  }
  delay(2000);
}
