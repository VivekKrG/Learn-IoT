#define sens A0
void setup() {
  pinMode(sens, OUTPUT);
  pinMode(15, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available())
      Serial.write(Serial.read());
     
  int value = (analogRead(sens)*500)/1023;
 if (value != 0) 
   Serial.write(value);
//  digitalWrite(BUILTIN_LED, 0); 
//  delay(300);
//  digitalWrite(15, 1);  
  delay(300);
}

