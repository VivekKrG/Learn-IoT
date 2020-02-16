const int sensorMin = 0; 
const int sensorMax = 1024; 
void setup() 
{
  Serial.begin(115200);
}

void loop()
{
  int sensorReading = analogRead(32);
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);
  Serial.println(sensorReading);//Actual Reading
  Serial.println(analogRead(39));
  /*switch (range)
    {
      case 0:
        Serial.println("RAINING");
        break;

      case 1:
        Serial.println("RAIN WARNING");
        break;

      case 2:
        Serial.println("NOT RAINING");
        break;
    }*/
  delay(1000); 
}
