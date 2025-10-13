/**
 * Ethernet test - sign
 *
 * listen to telnet and send text to sign
 * send things with e.g.,
 *   echo -e 'I am on a serial port!\0' | netcat 192.168.0.31 80
 *   printf 'AI IS FOR LOSERS\nTHINK FOR YOURSELF\0' | netcat 192.168.0.31 80
 */

// Arduino
#include "pins_arduino.h"
#include <Arduino.h>

// Ethernet
#define W5500_ETHERNET_SHIELD
#include <Ethernet.h>
#include <SPI.h>
byte mac[] = {0x60, 0xF2, 0xEC, 0x18, 0x05, 0xFE};
EthernetServer server(80);
String message1;
String message2;
uint32_t messageStartTime = 0;

// Bus sign
#include <CH_AS1100.h>
#include <pins.h>
#define NUM_CHIPS 32
Panel topRow = Panel(LOAD_PIN, NUM_CHIPS);
Panel bottomRow = Panel(LOAD_PIN_2, NUM_CHIPS);

// functions
void showText(Panel &p, char *msg);
String IPtoString(IPAddress &ip);

void setup() {
  // can't use INBUILT LED as it's pin 13, which is used by SPI for Ethernet
  // pinMode(ledPin, OUTPUT);
  // digitalWrite(ledPin, HIGH);

  // set up serial
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }

  // set up sign
  topRow.begin();
  bottomRow.begin();
  showText(topRow, (char *)"connecting to ethernet...");
  showText(bottomRow, (char *)"please wait... try reset if fail... ");

  // set up ethernet
  // disable SD SPI
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  Serial.println(F("Starting ethernet"));
  while (!Ethernet.begin(mac)) {
    Serial.print(F("."));
    delay(200);
  }
  Serial.print(F("Connected to… "));
  Serial.print(Ethernet.localIP());
  Serial.print(F(" on "));
  Serial.println(Ethernet.gatewayIP());

  // start listening for clients
  Serial.println(F("starting server"));
  server.begin();
  delay(1000);
  Serial.println(F("server started"));

  // get IP address as char*
  IPAddress ipAddress = Ethernet.localIP();
  String ipAddress_str =
      (String(ipAddress[0]) + '.' + String(ipAddress[1]) + '.' +
       String(ipAddress[2]) + '.' + String(ipAddress[3]));
  char ipAddress_arr[ipAddress_str.length() + 1];
  ipAddress_str.toCharArray(ipAddress_arr, ipAddress_str.length() + 1);

  // show IP on sign
  showText(topRow, (char *)"waiting for telnet...");
  showText(bottomRow, ipAddress_arr);
}

void loop() {
  // take input raw from telnet
  EthernetClient client = server.available();
  if (client) {
    Serial.println("---Got a client---");
    messageStartTime = millis();

    // compute each character (byte) sent to self
    int height = 0;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // end of message, quit
        if (c == '\0') {
          break;
        }
        // end of line, increase line counter and go to next line
        if (c == '\n') {
          height++;
          continue;
        }

        if (height == 0) { // line 1
          message1.concat(c);
        } else if (height == 1) { // line 2
          message2.concat(c);
        } else {
          ; // do nothing - we only have 2 line heights
          // but we must read the remainder of the request
        }
      }

      // timeout
      if (millis() - messageStartTime > 1000) {
        break;
      }
    }

    // debug: print message
    Serial.println("got messages:");
    Serial.println(message1);
    Serial.println(message2);

    // feedback messages to client
    client.println("---got write request for lines---");
    client.println(message1);
    client.println(message2);
    client.println("---no further content---");

    // show message on sign
    char message1_arr[message1.length() + 1];
    char message2_arr[message2.length() + 1];
    message1.toCharArray(message1_arr, message1.length() + 1);
    message2.toCharArray(message2_arr, message2.length() + 1);
    showText(topRow, message1_arr);
    showText(bottomRow, message2_arr);

    // reset and disconnect client
    message1 = "";
    message2 = "";
    Serial.println("---finished, disconnecting client---");
    delay(1);
    client.stop();
  }
}

void showText(Panel &p, char *msg) {
  p.clearDisplay();
  p.setCursor(0, 0);
  p.setTextColor(1);
  p.setTextSize(1); // pixel size multiplier
  p.println(msg);
  p.display();
}

String IPtoString(IPAddress &ip) { // IP v4 only
  String ips;
  ips.reserve(16);
  ips = ip[0];
  ips += '.';
  ips += ip[1];
  ips += '.';
  ips += ip[2];
  ips += '.';
  ips += ip[3];
  return ips;
}
