/*
 * Scrolling text
 * @alifeee
 */

#include <Arduino.h>

#include "AS1100.h"

AS1100 topRow = AS1100(D5, D6, D4);
AS1100 bottomRow = AS1100(D8, D7, D9);

void setup() {
  Serial.begin(115200);
  topRow.begin();
  bottomRow.begin();

  topRow.fillScreen(0);
  bottomRow.fillScreen(0);

  topRow.setCursor(1, 1);
  topRow.println("dredzik was here");
  topRow.display();

  bottomRow.setCursor(1, 1);
  bottomRow.println("ESP32C3");
  bottomRow.display();
}

void loop() {
  delay(1000);
}
