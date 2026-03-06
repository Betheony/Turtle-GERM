/*
  Non-blocking RGB LED + Fan Demo
  Inverted PWM: 0 = full brightness, 255 = off

  Features:
  - Smooth rainbow animation (HSV)
  - Fan cycles: ON 10s / OFF 5s
  - Max LED brightness capped at 50%
  - WHITE LED DISABLED
*/

// RED HAS A MAXIMUM OF 240 MILLIAMPS
const int FAN_PIN     = 2;
const int LED_R_PIN   = 5;
const int LED_G_PIN   = 6;
const int LED_B_PIN   = 9;
// const int LED_W_PIN   = 10;    // stays OFF

// ------------------------------
// Brightness limit (0 = max)
// 128 = 50% brightness cap
// ------------------------------
const int MAX_BRIGHT_RED = 0;
const int MAX_BRIGHT = 0;

// ------------------------------
// Global animation state
// ------------------------------
unsigned long currentMillis;

// Rainbow animation
unsigned long rainbowPrevMillis = 0;
const int rainbowSpeed = 20;     // ms between hue updates
int hue = 0;                     // 0–359 degrees

// Fan cycling (10s on, 5s off)
unsigned long fanPrevMillis = 0;
bool fanState = false;
const unsigned long fanOnTime  = 10000;
const unsigned long fanOffTime = 5000;


// ------------------------------
// Helper: HSV → RGB conversion
// ------------------------------
void hsvToRgb(int H, float& r, float& g, float& b) {
  float h = (float)H / 60.0;
  int i = (int)h;
  float f = h - i;
  float q = 1 - f;

  switch (i % 6) {
    case 0: r = 1; g = f; b = 0; break;
    case 1: r = q; g = 1; b = 0; break;
    case 2: r = 0; g = 1; b = f; break;
    case 3: r = 0; g = q; b = 1; break;
    case 4: r = f; g = 0; b = 1; break;
    case 5: r = 1; g = 0; b = q; break;
  }
}


// ------------------------------
// Task 1: Smooth rainbow animation
// ------------------------------
void updateRainbow() {
  if (currentMillis - rainbowPrevMillis >= rainbowSpeed) {
    rainbowPrevMillis = currentMillis;

    float r, g, b;
    hsvToRgb(hue, r, g, b);

    // Scale RGB from 0–1 → 0–MAX_BRIGHT (128)
    int R = MAX_BRIGHT_RED;
    int G = MAX_BRIGHT;
    //- int(g * MAX_BRIGHT);
    int B = MAX_BRIGHT;
    // - int(b * MAX_BRIGHT);

    analogWrite(LED_R_PIN, R);
    analogWrite(LED_G_PIN, G);
    analogWrite(LED_B_PIN, B);

    hue = (hue + 1) % 360;
  }
}


// ------------------------------
// Task 2: Fan 10s ON / 5s OFF cycle
// ------------------------------
void updateFan() {
  unsigned long interval = fanState ? fanOnTime : fanOffTime;

  if (currentMillis - fanPrevMillis >= interval) {
    fanPrevMillis = currentMillis;
    fanState = !fanState;
    digitalWrite(FAN_PIN, fanState ? HIGH : LOW);
  }
}


// ------------------------------
// SETUP
// ------------------------------
void setup() {
  pinMode(FAN_PIN, OUTPUT);
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
 //  pinMode(LED_W_PIN, OUTPUT);

  // WHITE LED ALWAYS OFF (full off on inverted pwm = 255)
  // analogWrite(LED_W_PIN, 255);

  digitalWrite(FAN_PIN, LOW);

  Serial.begin(9600);
  Serial.println("Starting non-blocking LED + Fan Demo (White OFF)");
}


// ------------------------------
// MAIN LOOP
// ------------------------------
void loop() {
  currentMillis = millis();

  updateRainbow();
  updateFan();
}
