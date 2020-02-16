void setup() {
 Serial.begin(115200);
}

void loop() {
   int sensorValue = analogRead(34);// read the input on analog pin 0:
  float voltage = sensorValue * (5.0 / 4096.0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  Serial.println(voltage); // print out the value you read:
  delay(1000);
} 
