#include "DHT.h"
#include "BluetoothSerial.h"
DHT dht2(15,DHT11);

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;
void setup() {
  Serial.begin(115200);
  Serial.println("**********System is starting**************");
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

}

void loop() {
  SerialBT.print("Temperature('C): ");
  SerialBT.println(dht2.readTemperature());
  SerialBT.print("Humidity(%): ");
  SerialBT.println(dht2.readHumidity());
  
  Serial.print("Temperature('C): ");
  Serial.print(dht2.readTemperature());
  Serial.print(" ");
  Serial.print("Humidity(%): ");
  Serial.println(dht2.readHumidity());
  delay(1000);
}
