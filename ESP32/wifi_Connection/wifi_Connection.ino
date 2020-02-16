#include "WiFi.h"

//char* ssid = "default";
// char* password = "default";
void setup() {
  Serial.begin(115200);

  Serial.println("Enter wifi/ssid");
  char  ssid[30] = "default";
  
  String string1, string2;
  
  while(!Serial.available()){}
  if(Serial.available())
  {
      string1 = Serial.readStringUntil('\n');
      delay(2);
  }

  string1.toCharArray(ssid,30);
  Serial.println("Enter Password");
  char password[30] = "default"; 
  
  while(!Serial.available()){}
  if(Serial.available())
  {
      string2 = Serial.readStringUntil('\n');
      delay(2);
  }
  
  string2.toCharArray(password,30);
  Serial.println("You have entered the PW");
  Serial.println(password);
  Serial.println("You have entered the SSID");
  Serial.println(ssid);
  
  delay(1000);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("Connecting to wifi..");
    }

    Serial.println("Connected");
    Serial.println(WiFi.localIP()); // Local IP of esp32
    Serial.println(WiFi.macAddress()); //mac address will be printed 
    
}

void loop() {  
}
