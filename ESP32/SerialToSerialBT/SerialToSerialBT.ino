//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#define led 2
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(led,OUTPUT);
  digitalWrite(led, HIGH);
}

void loop() {
  String readCommand= "";
  
  while (Serial.available()) {
    char c = Serial.read();
    SerialBT.write(c);
    Serial.write(c);
  }
      
  while (SerialBT.available()) {
    char c = SerialBT.read();
    Serial.write(c);
    readCommand += c;
    }
  if (readCommand.length() > 0){
      readCommand.trim();
      if (readCommand == "led on")
          digitalWrite(led,0);
      if (readCommand == "led off")
          digitalWrite(led,1);
  }
  
  delay(20);
}
