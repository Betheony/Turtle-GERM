#include "Config.h"
#include "Sensors.h"
#include "Actuators.h"

void setup() {
  Serial.begin(9600);
  initActuators();
  loadPlantParameters();
}

void loop() {
  float temp = readTemperature();
  float hum  = readHumidity();

  controlTemperature(temp);
  controlPump();
  controlLEDs();

  logSystemState(temp, hum);

  delay(1000);
}

