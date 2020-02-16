/*
 * esp32 scan all wifi nearby and list them with their ssid, strength, encryption type and mac address.
 * After that user have to put ssid and password to get connected.
 * Now connection status is displayed with mac address  and local ip
*/
#include <WiFi.h>

String translateEncryptionType(wifi_auth_mode_t encryptionType) {
 
  switch (encryptionType) {
    case (WIFI_AUTH_OPEN):
      return "Open";
    case (WIFI_AUTH_WEP):
      return "WEP";
    case (WIFI_AUTH_WPA_PSK):
      return "WPA_PSK";
    case (WIFI_AUTH_WPA2_PSK):
      return "WPA2_PSK";
    case (WIFI_AUTH_WPA_WPA2_PSK):
      return "WPA_WPA2_PSK";
    case (WIFI_AUTH_WPA2_ENTERPRISE):
      return "WPA2_ENTERPRISE";
  }
}
 
void scanNetworks() {
 
  int numberOfNetworks = WiFi.scanNetworks();
 
  Serial.print("Number of networks found: ");
  Serial.println(numberOfNetworks);
 
  for (int i = 0; i < numberOfNetworks; i++) {
 
    Serial.print("Network name: ");
    Serial.println(WiFi.SSID(i));
 
    Serial.print("Signal strength: ");
    Serial.println(WiFi.RSSI(i));
 
    Serial.print("MAC address: ");
    Serial.println(WiFi.BSSIDstr(i));
 
    Serial.print("Encryption type: ");
    String encryptionTypeDescription = translateEncryptionType(WiFi.encryptionType(i));
    Serial.println(encryptionTypeDescription);
    Serial.println("-----------------------");
 
  }
}
 
void connectToNetwork() {
  Serial.println("Please Select the wifi listed above");
  String string1, string2;
  char  ssid[30], password[30];
  Serial.println("Enter wifi/ssid");
  while(!Serial.available()){}
  if(Serial.available())
  {
      string1 = Serial.readStringUntil('\n');
  }
  string1.toCharArray(ssid,30);
  
  Serial.println("Enter Password"); 
  while(!Serial.available()){}
  if(Serial.available())
  {
      string2 = Serial.readStringUntil('\n');
  }
  string2.toCharArray(password,30);
  
  Serial.println("You have entered the PW");
  Serial.println(password);
  Serial.println("You have entered the SSID");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Establishing connection to WiFi..");
  }
 
  Serial.println("Connected to network");
 
}
 
void setup() {
 
  Serial.begin(115200);
 
  scanNetworks();
  connectToNetwork();
 
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());
 
  //WiFi.disconnect(true); // to disconnect to network.
  Serial.println(WiFi.localIP());
 
}
 
void loop() {}
