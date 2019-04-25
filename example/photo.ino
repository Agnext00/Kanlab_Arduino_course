/*
フォトセンサを動かすためのテストコード
*/


void setup() {
  /*int i;
  for(i=9; i<=13; i++){
    pinMode(i,OUTPUT);
  }*/
  
  Serial.begin(9600);        // シリアル通信の初期化

}
  
void loop() {
  // put your main code here, to run repeatedly:
  
  int analogPin = A0;
  int val = 0;
  int minLux = 620;
  int maxLux = 470;
  float Lux = 0;
  
  val = analogRead(analogPin);    // アナログピンを読み取る
  Serial.print("pin:  ");
  Serial.println(val);

  Lux = 700 - (val- maxLux)*4.55;    
  Serial.print("Lux:  ");
  Serial.println(Lux);

  delay(400);
}
