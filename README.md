# Arduino and IoT Laboratory Exercises

> **Portfolio status:** Source review completed. GitHub Actions is configured to compile firmware for the Arduino Mega 2560. **Physical hardware and live network/ThingSpeak behavior have not been verified.**

A curated collection of six Arduino Mega 2560 laboratory sketches exploring digital inputs, PWM, sensing, local networking, and cloud telemetry. The exercises are independent and intended for learning and reproducible demonstrations—not production monitoring or security-sensitive deployments.

## Projects

| Lab | Project | What it demonstrates | Dependencies |
|---|---|---|---|
| [01](lab-01-rgb-button-states/rgb_button_states/) | RGB LED + four buttons | Active-low buttons, PWM, color states | Mega 2560, common-anode RGB LED |
| [02](lab-02-ultrasonic-ranging/ultrasonic_ranging/) | Ultrasonic range | Trigger/echo timing, timeouts, distance conversion | Mega 2560, HC-SR04 |
| [03](lab-03-sensor-threshold-alarm/sensor_threshold_alarm/) | Sensor threshold alarm | Analog voltage readings, thresholds, LED, buzzer | Mega 2560, analog sensors |
| [04](lab-04-ethernet-client/ethernet_client/) | Ethernet HTTP client | DHCP, HTTP request/response | Mega 2560, Ethernet shield |
| [05](lab-05-ethernet-server/ethernet_server/) | Local button web server | Serve a simple HTML status page over LAN | Mega 2560, Ethernet shield |
| [06](lab-06-thingspeak-ultrasonic/thingspeak_ultrasonic/) | ThingSpeak telemetry | Send echo duration and distance to a cloud channel | Mega 2560, Ethernet shield, ThingSpeak library |

## Start here

1. Install the **Arduino IDE** or **Arduino CLI**.
2. Select **Arduino Mega or Mega 2560** (ATmega2560) as the board. Many examples use pins unavailable on Uno; do not select Uno.
3. Read [hardware and pin mapping](docs/HARDWARE_AND_PINOUT.md) before connecting components.
4. Open a single sketch folder and compile/upload its matching `.ino` file (folder and file names match).
5. For Labs 04–06, install the Arduino **Ethernet** library and use a compatible Ethernet shield. For Lab 06, install **ThingSpeak** as well.
6. For Lab 06 only, copy `secrets.example.h` to `secrets.h` beside the sketch, then fill in **fresh personal credentials**. The real `secrets.h` is ignored by Git.
7. Validate behavior using [test cases and acceptance criteria](docs/TEST_PLAN.md).

### Local compilation

With `arduino-cli` and the Mega AVR board core installed:

```bash
arduino-cli core install arduino:avr
arduino-cli lib install Ethernet
arduino-cli lib install ThingSpeak
cp lab-06-thingspeak-ultrasonic/thingspeak_ultrasonic/secrets.example.h lab-06-thingspeak-ultrasonic/thingspeak_ultrasonic/secrets.h
bash scripts/compile.sh
```

The sample configuration lets the ThingSpeak sketch **compile**, but it cannot send real updates without a valid channel ID and write key. Never commit a populated `secrets.h`.

A GitHub Actions workflow is included to compile all six sketches for **Arduino Mega 2560**. A passing build does not establish that wiring, sensors, Ethernet, or cloud services work in real conditions.

## What was improved

- Renamed date-based sketches into purpose-based projects; removed duplicated Lab 06 copies and empty template files.
- Clarified RGB LED polarity and fixed dim-white PWM behavior.
- Added explicit ultrasonic no-echo handling and documented assumed ambient temperature.
- Distinguished analog thermistor **voltage** from calibrated degrees Celsius.
- Reimplemented the two generic Ethernet demonstrations with classroom-safe, concise code rather than republishing upstream Arduino example text.
- Removed original campus LAN addresses and ThingSpeak keys from publishable source. Lab 06 uses local-only credentials and DHCP.
- Added hardware tables, setup instructions, a test plan, repository hygiene, and automated compile workflow.

## Limitations and safety

- Labs have not been hardware-tested or independently verified with live ThingSpeak/Ethernet in this review.
- Labs 04–06 use unencrypted **HTTP** for educational demonstrations; never transmit personal/private data or expose the local server to the public Internet.
- The Lab 03 thresholds depend on the particular classroom circuit and need calibration for other sensors.
- The original archive contained real ThingSpeak credentials; **rotate/revoke them before reusing related accounts**. See [security and provenance](docs/SECURITY_AND_PROVENANCE.md).
- The Arduino sketches are educational examples. They must not be used as safety-critical alarms or motor-protection systems.

## References

- [Arduino documentation](https://docs.arduino.cc/)
- [Arduino CLI](https://arduino.github.io/arduino-cli/)
- [Arduino Ethernet library](https://docs.arduino.cc/libraries/ethernet/)
- [MathWorks ThingSpeak Arduino library](https://github.com/mathworks/thingspeak-arduino)

## License and provenance

These sketches are refactored from the owner's course exercises. The Ethernet examples have been rewritten around the original learning objectives; the generic Ethernet client/server concepts are also covered in official Arduino examples. No open-source license is selected for this repository yet.
