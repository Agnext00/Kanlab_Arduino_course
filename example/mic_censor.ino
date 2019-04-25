void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int MIC_OUTPUT = 1;
  int val = 0;
  
  val = analogRead(MIC_OUTPUT);    // アナログピンを読み取る
  Serial.print("pin:  ");
  Serial.println(val);
  delay(30);
}
