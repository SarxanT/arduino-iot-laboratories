// Lab 06: upload HC-SR04 echo duration and distance to ThingSpeak.
// Arduino Mega + Ethernet shield; uses local secrets.h (never commit it).
// Adapted from the author's ultrasonic coursework logic, not a vendor sketch.

#include <SPI.h>
#include <Ethernet.h>
#include <ThingSpeak.h>
#include "secrets.h"

byte mac[] = SECRET_MAC;
const unsigned long CHANNEL_ID = SECRET_CH_ID;
const char *WRITE_KEY = SECRET_WRITE_APIKEY;
const byte TRIG_PIN = A3;
const byte ECHO_PIN = A4;
EthernetClient network;
bool networkReady = false;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
  Ethernet.init(10);

  if (CHANNEL_ID == 0 || String(WRITE_KEY) == "REPLACE_WITH_YOUR_WRITE_KEY") {
    Serial.println(F("Set your own ThingSpeak channel ID and write key in local secrets.h."));
    return;
  }
  if (Ethernet.begin(mac) == 0) {
    Serial.println(F("Ethernet unavailable. Check shield, cable, and DHCP."));
    return;
  }
  ThingSpeak.begin(network);
  networkReady = true;
  Serial.println(F("ThingSpeak uploader ready."));
}

void loop() {
  if (!networkReady) { delay(20000); return; }
  Ethernet.maintain();

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  const unsigned long echoUs = pulseIn(ECHO_PIN, HIGH, 30000UL);
  if (echoUs == 0) {
    Serial.println(F("No echo detected; skipped cloud upload."));
  } else {
    // Approximately 0.0343 cm per microsecond at room temperature.
    const float distanceCm = echoUs * 0.0343f / 2.0f;
    ThingSpeak.setField(1, static_cast<long>(echoUs));
    ThingSpeak.setField(2, distanceCm);
    const int status = ThingSpeak.writeFields(CHANNEL_ID, WRITE_KEY);
    Serial.print(F("Distance_cm:")); Serial.print(distanceCm, 1);
    Serial.print(F("\tThingSpeak_HTTP:")); Serial.println(status);
  }
  // This project deliberately sends at most one update per 20 seconds.
  delay(20000);
}
