#define PIN_HEATER 12 // D14(A0)
#define PIN_SENSOR 13 // D15(A1)
#define PIN_OUTPUT 1 // A3
void setup() {
 pinMode(PIN_HEATER,OUTPUT);
 pinMode(PIN_SENSOR,OUTPUT);
 digitalWrite(PIN_HEATER,HIGH); // Heater Off
 digitalWrite(PIN_SENSOR,LOW); // Sensor Pullup Off

 Serial.begin(9600);
}
void loop() {
 int val=0;

 delay(237);
 digitalWrite(PIN_SENSOR,HIGH); // Sensor Pullup On
 delay(3);
 val = analogRead(PIN_OUTPUT); // Get Sensor Voltage
 delay(2);
 digitalWrite(PIN_SENSOR,LOW); // Sensor Pullup Off

 digitalWrite(PIN_HEATER,LOW); // Heater On
 delay(8);
 digitalWrite(PIN_HEATER,HIGH); // Heater Off
 Serial.println(val);
}
