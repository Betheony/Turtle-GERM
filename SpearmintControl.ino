// Blink test on built-in LED (usually pin 13 on Arduino Uno)
// Confirms the board is alive and uploading

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // ON
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);   // OFF
  delay(1000);
}

