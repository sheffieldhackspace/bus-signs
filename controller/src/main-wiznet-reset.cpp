#include <Arduino.h>

void setup() {
  // WIZNET RESET AND INITIALIZE
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW); // reset the WIZ820io
  delay(10);
  digitalWrite(9, HIGH); // reset the WIZ820io
}

void loop() {}
