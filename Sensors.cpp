#include <Arduino.h>
#include "Config.h"

float readTemperature() {
  int raw = analogRead(TEMP_SENSOR_PIN);
  // Replace with real formula for your sensor
  return (raw / 1023.0) * 50.0; 
}

float readHumidity() {
  int raw = analogRead(HUM_SENSOR_PIN);
  return (raw / 1023.0) * 100.0;
}

