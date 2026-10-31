# Security and source provenance

## Credentials

The original privately supplied coursework archive contained real ThingSpeak write/TalkBack API keys in both a Python configuration file and an Arduino `secrets.h`. Those values have **not** been copied into this repository. Before reusing the associated ThingSpeak project, rotate/revoke those previous keys and issue new ones. Treat old keys as potentially exposed wherever the original archive was shared.

Lab 06 stores secrets in a local `secrets.h` created from the public `secrets.example.h`. The `.gitignore` rule `**/secrets.h` prevents routine Git adds; still inspect diffs and commits. Never commit real API keys, passwords, private Wi-Fi details, or private MQTT topics.

The original labs also included classroom network addresses. The publishable Ethernet sketches instead use DHCP and do not contain those addresses. The included MAC addresses are examples, **not guaranteed unique**.

## Network boundaries

- Lab 05's HTTP server is intended for a trusted local network only. Do not forward its port to the public Internet.
- The Ethernet demonstrations use plain HTTP, not TLS. Do not transmit sensitive measurements or credentials on untrusted networks.
- The ThingSpeak library sketch is a learning example and should not be treated as a secure telemetry stack.

## Provenance and excluded materials

- Labs 01–03 and 06 were drawn from the owner's coursework source and refined for readability, consistency, and guardrails.
- Labs 04–05 demonstrate generic Arduino Ethernet concepts. Their portfolio versions were **reimplemented**; they do not copy full upstream tutorial/example texts.
- The original Lab 06 archive repeated the earlier Ethernet examples; duplicates and empty Arduino template sketches are excluded.
- Original reports (`.docx`/`.odt`) and their screenshots were not included. They may include instructor/course identifiers and are not required to run the code.
- This repository does not contain Python virtual environments, binary files, measurement logs, or the more advanced ESP32 MQTT/ThingSpeak coursework project.

No third-party code or library files are vendored. Libraries are obtained from their official package managers. No open-source license has been selected for the author's code yet.
