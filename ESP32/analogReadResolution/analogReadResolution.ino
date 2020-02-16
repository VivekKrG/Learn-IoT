void setup() {
  Serial.begin(115200);
  pinMode(15,INPUT);
  pinMode(2,INPUT);
  analogReadResolution(12);
}

void loop() {
  Serial.println((float)analogRead(15)*330/4095);
  Serial.println((float)analogRead(2)*330/4095);
  delay(2000);
}
