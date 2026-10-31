// Lab 05: local Ethernet HTTP server displaying three button states.
// Written for this portfolio; designed for trusted classroom LANs only.

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0x02, 0x19, 0x26, 0x00, 0x05, 0x01}; // Example local MAC: check uniqueness on your LAN.
const byte BUTTON_PINS[] = {A1, A2, A3};
EthernetServer server(80);
bool ready = false;

void setup() {
  Serial.begin(9600);
  for (byte pin : BUTTON_PINS) pinMode(pin, INPUT_PULLUP);
  Ethernet.init(10);
  if (Ethernet.begin(mac) == 0) {
    Serial.println(F("DHCP failed; check shield, cable and network."));
    return;
  }
  server.begin();
  ready = true;
  Serial.print(F("Open http://"));
  Serial.println(Ethernet.localIP());
}

void loop() {
  if (!ready) return;
  Ethernet.maintain();
  EthernetClient client = server.available();
  if (!client) return;

  bool blankLine = true;
  bool headersDone = false;
  unsigned int bytesRead = 0;
  const unsigned long startMs = millis();
  while (client.connected() && millis() - startMs < 2000UL && bytesRead < 1024U) {
    if (!client.available()) continue;
    char c = client.read();
    ++bytesRead;
    if (c == '\n' && blankLine) { headersDone = true; break; }
    if (c == '\n') blankLine = true;
    else if (c != '\r') blankLine = false;
  }

  if (headersDone) {
    client.println(F("HTTP/1.1 200 OK"));
    client.println(F("Content-Type: text/html; charset=utf-8"));
    client.println(F("Connection: close"));
    client.println(F("Refresh: 5"));
    client.println();
    client.println(F("<!doctype html><html><head><title>Button monitor</title></head><body>"));
    client.println(F("<h1>Arduino button monitor</h1>"));
    for (byte i = 0; i < 3; ++i) {
      client.print(F("<p>Button "));
      client.print(i + 1);
      client.print(F(": "));
      client.print(digitalRead(BUTTON_PINS[i]) == LOW ? F("PRESSED") : F("RELEASED"));
      client.println(F("</p>"));
    }
    client.println(F("</body></html>"));
  }
  delay(2);
  client.stop();
}
