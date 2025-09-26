#include <Arduino.h>
#include "Config.h"

// State variables
unsigned long lastPumpCycle = 0;
unsigned long lastLightCycle = 0;
bool pumpState = false;
bool lightState = false;

void initActuators() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
  pinMode(LED_W_PIN, OUTPUT);
}

void loadPlantParameters() {
  Serial.println("Loaded spearmint parameters:");
  Serial.print("Temp "); Serial.print(TEMP_LOW_CUTOFF);
  Serial.print("–"); Serial.print(TEMP_HIGH_CUTOFF);
  Serial.print(" °C, pH "); Serial.print(PH_LOW);
  Serial.print("–"); Serial.println(PH_HIGH);
}

void controlTemperature(float temp) {
  if (temp < TEMP_LOW_CUTOFF) {
    digitalWrite(RELAY_PIN, HIGH); 
    Serial.println("Heating ON");
  } else if (temp > TEMP_HIGH_CUTOFF) {
    digitalWrite(RELAY_PIN, HIGH); 
    Serial.println("Cooling ON");
  } else {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Temperature stable");
  }
}

void controlPump() {
  unsigned long now = millis();
  if (!pumpState && (now - lastPumpCycle >= PUMP_CYCLE_PERIOD)) {
    pumpState = true;
    lastPumpCycle = now;
    digitalWrite(PUMP_PIN, HIGH);
    Serial.println("Pump ON");
  }
  if (pumpState && (now - lastPumpCycle >= PUMP_SPRAY_DURATION)) {
    pumpState = false;
    digitalWrite(PUMP_PIN, LOW);
    Serial.println("Pump OFF");
  }
}

void controlLEDs() {
  unsigned long now = millis();
  if (!lightState && (now - lastLightCycle >= LIGHT_OFF_DURATION)) {
    lightState = true;
    lastLightCycle = now;
    analogWrite(LED_R_PIN, 200);
    analogWrite(LED_B_PIN, 150);
    analogWrite(LED_W_PIN, 100);
    Serial.println("Lights ON");
  }
  if (lightState && (now - lastLightCycle >= LIGHT_ON_DURATION)) {
    lightState = false;
    analogWrite(LED_R_PIN, 0);
    analogWrite(LED_B_PIN, 0);
    analogWrite(LED_W_PIN, 0);
    Serial.println("Lights OFF");
  }
}

void logSystemState(float temp, float hum) {
  Serial.print("Temp: "); Serial.print(temp); Serial.print(" C");
  Serial.print(", Hum: "); Serial.print(hum); Serial.print(" %");
  Serial.print(", Pump: "); Serial.print(pumpState);
  Serial.print(", Lights: "); Serial.println(lightState);
}

