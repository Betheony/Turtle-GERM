#include <Arduino.h>
#include "Config.h"

// ---------------- State variables ----------------
unsigned long lastPumpCycle = 0;
unsigned long lastLightCycle = 0;
bool pumpState = false;
bool lightState = false;

// ---------------- Initialization ----------------
void initActuators() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);

  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
  pinMode(LED_W_PIN, OUTPUT);

  // Ensure all LEDs start off
  analogWrite(LED_R_PIN, 0);
  analogWrite(LED_G_PIN, 0);
  analogWrite(LED_B_PIN, 0);
  analogWrite(LED_W_PIN, 0);
}

void loadPlantParameters() {
  Serial.println("Loaded spearmint parameters:");
  Serial.print("Temp "); Serial.print(TEMP_LOW_CUTOFF);
  Serial.print("–"); Serial.print(TEMP_HIGH_CUTOFF);
  Serial.print(" °C, pH "); Serial.print(PH_LOW);
  Serial.print("–"); Serial.println(PH_HIGH);
}

// ---------------- Temperature Control ----------------
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

// ---------------- Pump Control ----------------
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

// ---------------- LED PWM Control ----------------
void setLEDColor(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  // Direct PWM output, 0–255 duty cycle
  analogWrite(LED_R_PIN, r);
  analogWrite(LED_G_PIN, g);
  analogWrite(LED_B_PIN, b);
  analogWrite(LED_W_PIN, w);
}

void controlLEDs() {
  unsigned long now = millis();

  // After the OFF period, turn lights ON
  if (!lightState && (now - lastLightCycle >= LIGHT_OFF_DURATION)) {
    lightState = true;
    lastLightCycle = now;

    // Example brightness balance (tune freely)
    setLEDColor(200, 120, 150, 100);
    Serial.println("Lights ON");
  }

  // After the ON period, turn all LEDs OFF
  if (lightState && (now - lastLightCycle >= LIGHT_ON_DURATION)) {
    lightState = false;
    setLEDColor(0, 0, 0, 0);
    Serial.println("Lights OFF");
  }
}

// ---------------- Logging ----------------
void logSystemState(float temp, float hum) {
  Serial.print("Temp: "); Serial.print(temp); Serial.print(" C");
  Serial.print(", Hum: "); Serial.print(hum); Serial.print(" %");
  Serial.print(", Pump: "); Serial.print(pumpState);
  Serial.print(", Lights: "); Serial.println(lightState);
}
