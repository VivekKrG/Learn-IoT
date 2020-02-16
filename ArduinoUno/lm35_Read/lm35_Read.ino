void setup() {
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(A0)*500/1023);
  delay(1000);
}
