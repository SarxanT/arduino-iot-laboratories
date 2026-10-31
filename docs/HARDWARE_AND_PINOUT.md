# Hardware and pin mapping

**Target for all six exercises:** Arduino Mega 2560, generally using 5 V logic. This is based on the original sketches' high-numbered pins (43, 44, 48 and A8). Verify your actual board and circuit before trying a sketch; these configurations are not for the ESP32.

| Lab | Components | Key connections and assumptions |
| --- | --- | --- |
| 01 RGB | 4 normally-open buttons, common-anode RGB LED, three current-limiting resistors | Buttons: D2, D3, D43, D44 → GND when pressed. LED: red D12, green D11, blue D10 via resistors; common anode → 5 V. PWM values inverted for common anode. |
| 02 Range | HC-SR04 ultrasonic sensor | TRIG D48, ECHO D8, VCC 5 V, common GND. Assumed ambient temperature: 23.5 °C; **not measured**. |
| 03 Alarm | 2 analog sensor circuits, common-anode status LED, passive buzzer | Light voltage A0, thermistor divider voltage A1, green D11, red D12, buzzer A8 (digital output). Sensors must keep analog inputs within the board's 0–5 V reference. |
| 04 Client | Ethernet shield and an Ethernet network with DHCP | Ethernet shield on Mega 2560; typical chip-select D10. Uses HTTP to `example.com` port 80; no private data. |
| 05 Server | Ethernet shield, 3 buttons | Buttons A1, A2, A3 to GND with internal pull-ups. Server listens on LAN port 80. |
| 06 Cloud | Ethernet shield, HC-SR04, ThingSpeak channel | HC-SR04 TRIG A3, ECHO A4, VCC to a suitable 5 V supply, GND to board GND. ThingSpeak Field 1 = echo time (µs), Field 2 = distance (cm). |

### Important notes

- Use an appropriate current-limiting resistor for **each** RGB LED color channel; do not connect bare LEDs directly to I/O pins.
- Lab 06 deliberately **does not** power the HC-SR04 from arbitrary I/O pins, unlike the original experimental sketch. Use the board's suitable power/ground connections.
- The analog threshold example is a classroom demonstration. Sensor output calibration and wiring depend on the specific LDR/thermistor divider you build.
- For Ethernet shields, confirm the board/shield SPI header compatibility and correct chip-select pin. MAC addresses in Labs 04–06 are **sample locally administered values**; change them if there is any LAN address collision.
- Power off the board when changing wiring. Never connect the board's low-voltage pins directly to mains-powered equipment or motor power circuits.
