#define SENSOR 4
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  Serial.println("Sensor start");
}

void loop() {
  sensorValue = analogRead(SENSOR);
  Serial.print("Value: "); Serial.println(sensorValue); 
  digitalWrite(2, LOW);
  delay(200);
  digitalWrite(2, HIGH);
}
