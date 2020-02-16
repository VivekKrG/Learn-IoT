#include <WiFi.h>
#include <WifiLocation.h>

const char* googleApiKey = "AIzaSyCYNXIYINPmTNIdusMjJloS4_BXSOff1_g";
const char* ssid = "mywifi";
const char* passwd = "98769876";

WifiLocation location(googleApiKey);

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_MODE_STA);
    WiFi.begin(ssid, passwd);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        delay(500);
    }
    
    Serial.println(location.getSurroundingWiFiJson());
}

void loop() {
    location_t loc = location.getGeoFromWiFi();
    Serial.println("Latitude: " + String(loc.lat, 7));
    Serial.println("Longitude: " + String(loc.lon, 7));
    Serial.println("Accuracy: " + String(loc.accuracy));
    delay(5000);
}
