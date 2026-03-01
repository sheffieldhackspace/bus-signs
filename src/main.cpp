/*
 * Scrolling text
 * @alifeee
 */

#include "Arduino.h"
#include <AS1100.h>
#include <pins.h>

AS1100 topRow = AS1100(LOAD_PIN_TOP);
AS1100 bottomRow = AS1100(LOAD_PIN_BOTTOM);

void setup() {
  Serial.begin(115200);
  topRow.begin();
  bottomRow.begin();

  topRow.fillScreen(0);
  bottomRow.fillScreen(0);

  topRow.setCursor(1, 1);
  topRow.println("LOL ESP32C3");
  topRow.display();

  bottomRow.setCursor(1, 1);
  bottomRow.println("Well that was fast...");
  bottomRow.display();
}

void loop() {
  delay(1000);
}
