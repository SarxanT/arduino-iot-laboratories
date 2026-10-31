# Validation plan and expected results

## Validation status

- [x] Source files reorganized, duplicates removed, project documentation written.
- [x] Basic static repository and credential checks passed at package preparation time.
- [x] Six Arduino Mega sketches compiled in [GitHub Actions on 31 October 2026](https://github.com/SarxanT/arduino-iot-laboratories/actions/runs/41196010207).
- [ ] Real board + component tests.
- [ ] Ethernet DHCP, network-client, and server tests.
- [ ] Live ThingSpeak channel upload with a new key.

## Functional acceptance checks (run on trusted, low-voltage lab hardware)

| Lab | Test | Expected output |
| --- | --- | --- |
| 01 | Press M1, M2, M3, M4, then release | Purple, red, bright white, dim white, then off; serial state messages |
| 02 | Move a target at known distances | Nonzero `Distance_cm` and `Duration_us` readings; disconnected echo reports timeout |
| 03 | Vary light/thermistor divider voltages around configured limits | Normal = green; one fault = red; two faults = red plus buzzer; voltage readings printed |
| 04 | Connect the shield to DHCP-enabled network | Prints local IP, sends example HTTP GET; output depends on network/DNS availability |
| 05 | Visit printed LAN address in a browser on same network; press buttons | Web page shows each button as `PRESSED`/`RELEASED`; refresh every ~5 s |
| 06 | Configure a fresh channel/key; vary HC-SR04 distance | ThingSpeak Field 1 = echo duration; Field 2 = distance; uploads spaced by ≥20 s |

### Compile checks

Run the following only after installing Arduino CLI, the AVR core, and the libraries described in the README:

```bash
python3 scripts/check_structure.py
bash scripts/compile.sh
```

The same compilation is configured in `.github/workflows/compile-arduino.yml` and runs automatically after publishing. A green CI result is evidence of a successful **compile**, not of a successful physical or cloud test.

### Evidence to add after hardware testing

- Console outputs/small screenshots with secrets and personal details hidden.
- Board and sensor photos with no identifying information.
- Exact board model/shield revision and library versions.
- Successful and failed test cases, dated truthfully.
