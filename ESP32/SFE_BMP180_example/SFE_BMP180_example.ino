#include <SFE_BMP180.h>
#include <Wire.h>
SFE_BMP180 pressure;
#define ALTITUDE 505.0 // Altitude of SparkFun's HQ in Boulder, CO. in meters

void setup()
{
  Serial.begin(115200);
  
  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    Serial.println("BMP180 init fail");
    while(1);
  }
}

void loop()
{
  char status;
  double T,P,p0,a;
  
  Serial.println();
  Serial.print("provided altitude: ");
  Serial.print(ALTITUDE,0);
  Serial.print(" meters, ");
  Serial.print(ALTITUDE*3.28084,0);
  Serial.println(" feet");

  status = pressure.startTemperature();
  if (status != 0)
  {
    delay(status);

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      Serial.print("temperature: ");
      Serial.print(T,2);
      Serial.print(" deg C, ");
      
      status = pressure.startPressure(3);
      if (status != 0)
      {
        delay(status);
        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          Serial.print("absolute pressure: ");
          Serial.print(P,2);
          Serial.print(" mb, "); //To convert it into other unit use: (P*0.0295333727,2) it is in inHg
                    
          p0 = pressure.sealevel(P,ALTITUDE); // we're at 505 meters (Hyderabad, India)
          Serial.print("relative (sea-level) pressure: ");
          Serial.print(p0,2);
          Serial.print(" mb, ");
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temper ature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
  delay(5000);
}
