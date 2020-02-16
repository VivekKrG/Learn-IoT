/*
 * ESP32 has on chip temperature sensor,
 * This sensor is not usable to monitor external temperature,
 * It is used to monitor its core temperature. 
 * In this tutorial we are monitoring on chip temperature sensor data.
 */

#ifdef __cplusplus
  extern "C" {
 #endif

  uint8_t temprature_sens_read();

#ifdef __cplusplus
}
#endif

uint8_t temprature_sens_read();

void setup() {
  Serial.begin(115200);
}
void loop() {
  Serial.print("Temperature: ");
  
  // Convert raw temperature in F to Celsius degrees
  Serial.print((temprature_sens_read() - 32) / 1.8);
  Serial.println(" C");
  delay(1000);
}
