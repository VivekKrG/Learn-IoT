void setup() {
  Serial.begin(115200); //Baud rate
}

void loop() {
  float sensor_volt = 0.000000; //Define variable for sensor voltage
  float RS_air = 0.000000; //Define variable for sensor resistance
  float R0 = 0.000000; //Define variable for R0
  float sensorValue = 0.000000; //Define variable for analog readings
  for (int x = 0 ; x < 500 ; x++) //Start for loop
  {
    sensorValue = sensorValue + ((float)analogRead(32)/500.0); //Add analog values of sensor 500 times
    //Serial.print(analogRead(32));
    delay(50);
  }
  Serial.println((float)analogRead(32));
  Serial.println(sensorValue); //Take average of readings
  sensor_volt = sensorValue * (3.3 / 4096.0); //Convert average to voltage
  Serial.println(sensor_volt);
  sensor_volt = 5.0*sensor_volt/3.3; //to mapping into 5.0 volt scale
  Serial.println(sensor_volt);
  //formula is (Vc/Vo-1)*Rl; here Rl is taken 20.0 it can be any valu as
  //it will be cancelled on taking ration
  RS_air = (20.0*(5.0/ sensor_volt-1)); //Calculate RS in fresh air
  R0 = RS_air / 4.4; //Calculate R0

  Serial.print("R0 = "); //Display "R0"
  Serial.println(R0); //Display value of R0
  delay(100); //Wait 1 second
}



//Output readed as R0= 9.5, use it
