/*
温湿度計を用いたLED点灯
*/

#include <DHT.h>

const int PIN_DHT = 8;
DHT dht(PIN_DHT,DHT11);

void setup() {
    int i;
  for(i=1; i<=7; i++){
    pinMode(i,OUTPUT);
  }
  
  Serial.begin(9600);
  Serial.println("DHT11");
  dht.begin();
}

void loop() {
  delay(3000);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.print("Humidity:  ");
  Serial.print(humidity);
  Serial.println("%\t");
  Serial.print("Temperature:  ");
  Serial.print(temperature);
  Serial.println(" *C");

  digitalWrite(7,LOW);
  digitalWrite(6,LOW);
  digitalWrite(5,LOW);
  digitalWrite(4,LOW);
  digitalWrite(3,LOW);
 
  
  
  if(humidity>80){
    if(temperature<25){
      digitalWrite(4,HIGH);
      digitalWrite(3,HIGH);
    }else if(temperature>=25){
      digitalWrite(3,HIGH);
    }
  }else if(humidity>=40){
    if(temperature<25){
      digitalWrite(6,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(4,HIGH);
      digitalWrite(3,HIGH);
    }else if(temperature>=25){
      digitalWrite(5,HIGH);
      digitalWrite(4,HIGH);
      digitalWrite(3,HIGH);
    }
  }else if(humidity<40){
    if(temperature<=23){
      digitalWrite(7,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(4,HIGH);
      digitalWrite(3,HIGH);
    }else if(temperature>23){
      digitalWrite(6,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(4,HIGH);
      digitalWrite(3,HIGH);      
    }
  }else{
      digitalWrite(3,HIGH);
  }
}
