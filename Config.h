#ifndef CONFIG_H
#define CONFIG_H

// Temperature range (°C)
const float TEMP_LOW_CUTOFF  = 18.0;
const float TEMP_HIGH_CUTOFF = 24.0;

// pH (for reference, not enforced)
const float PH_LOW  = 6.5;
const float PH_HIGH = 7.0;

// Pump flow rate (gal/sec per nozzle)
const float PUMP_RATE_GAL_SEC = 0.006;
const float SPRAY_TARGET_GAL  = 0.05;
const unsigned long PUMP_SPRAY_DURATION =
    (SPRAY_TARGET_GAL / PUMP_RATE_GAL_SEC) * 1000; // ms
const unsigned long PUMP_CYCLE_PERIOD = 3600000UL; // 1 hr

// Light cycle (12h on / 12h off)
const unsigned long LIGHT_ON_DURATION  = 43200000UL; // 12h
const unsigned long LIGHT_OFF_DURATION = 43200000UL; // 12h

// Pin assignments
const int RELAY_PIN   = 2;   // Relay for Peltier + fans
const int PUMP_PIN    = 8;   // Pump MOSFET

const int LED_R_PIN = 5;   // Red channel
const int LED_G_PIN = 6;   // Green channel
const int LED_B_PIN = 9;   // Blue channel
const int LED_W_PIN = 10;  // White channel

const int TEMP_SENSOR_PIN = A0;
const int HUM_SENSOR_PIN  = A1;

#endif

