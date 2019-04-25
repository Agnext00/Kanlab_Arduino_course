 #include "Air_Quality_Sensor.h"

AirQualitySensor sensor(A0);

void setup(void) {
  Serial.begin(9600);
  int Air_quality[500];
  while (!Serial);

  Serial.println("Waiting sensor to init...");
  delay(10000);

  if (sensor.init()) {
    Serial.println("Sensor ready.");
  }
  else {
    Serial.println("Sensor ERROR!");
  }
}

void loop(void) {
  int quality = sensor.slope();

  Serial.print("Sensor value: ");
  Serial.println(sensor.getValue());
  
  if (quality == AirQualitySensor::FORCE_SIGNAL) {
    Serial.println("High pollution! Force signal active.\n");
  }
  else if (quality == AirQualitySensor::HIGH_POLLUTION) {
    Serial.println("High pollution!\n");
  }
  else if (quality == AirQualitySensor::LOW_POLLUTION) {
    Serial.println("Low pollution!\n");
  }
  else if (quality == AirQualitySensor::FRESH_AIR) {
    Serial.println("Fresh air.\n");
  }

  delay(1000);
}
