/*
 * Listen to SoftwareSerial/UART on pins 3/4
 * @alifeee
 */

#include "Arduino.h"
#include <SoftwareSerial.h>

SoftwareSerial link(3, 4); // Rx, Tx

String message;

void processMessage(String message);

void setup() {
  link.begin(9600); // setup software serial
  link.listen();
  Serial.begin(115200); // setup serial monitor
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.print("reset...");

  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  char character;

  while (link.available()) {
    character = link.read();
    // Serial.println("got character");
    // Serial.println(character);
    if (character == '\0') {
      // Serial.println("got message");
      // Serial.println(message);
      processMessage(message);
      message = "";
    } else {
      message.concat(character);
    }
  }
}

void processMessage(String message) {
  Serial.println("message");
  for (int i = 0; i < 432; i++) {
    for (int a = 7; a >= 0; a--) {
      // deal with each pixel value here (probably using setPixel)
      Serial.print((message[i] >> a) & 1);
    }
  }
  Serial.println("");
}
