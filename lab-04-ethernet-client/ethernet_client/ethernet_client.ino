// Lab 04: compact Ethernet HTTP client, written for this portfolio.
// Inspired by the Arduino Ethernet example's learning objective, not a copy.
// HTTP (port 80) is an intentionally unencrypted demo; send no private data.

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0x02, 0x19, 0x26, 0x00, 0x04, 0x01}; // Example local MAC: check uniqueness on your LAN.
const char HOST[] = "example.com";
EthernetClient client;

void setup() {
  Serial.begin(9600);
  Ethernet.init(10);  // Typical Ethernet shield chip-select pin.
  if (Ethernet.begin(mac) == 0) {
    Serial.println(F("DHCP failed: check shield, cable and network configuration."));
    return;
  }
  Serial.print(F("Local IP: "));
  Serial.println(Ethernet.localIP());

  if (!client.connect(HOST, 80)) {
    Serial.println(F("HTTP connection failed."));
    return;
  }
  client.println(F("GET / HTTP/1.1"));
  client.println(F("Host: example.com"));
  client.println(F("Connection: close"));
  client.println();

  const unsigned long startMs = millis();
  while ((client.connected() || client.available()) && millis() - startMs < 7000UL) {
    while (client.available()) Serial.write(client.read());
  }
  client.stop();
  Serial.println(F("\nHTTP demo finished."));
}

void loop() {
  // Intentionally a single request per boot.
}
