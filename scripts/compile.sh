#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
if ! command -v arduino-cli >/dev/null 2>&1; then
  echo 'arduino-cli is not installed. See README.md.' >&2
  exit 1
fi
FQBN="${FQBN:-arduino:avr:mega}"
for sketch in \
  lab-01-rgb-button-states/rgb_button_states \
  lab-02-ultrasonic-ranging/ultrasonic_ranging \
  lab-03-sensor-threshold-alarm/sensor_threshold_alarm \
  lab-04-ethernet-client/ethernet_client \
  lab-05-ethernet-server/ethernet_server \
  lab-06-thingspeak-ultrasonic/thingspeak_ultrasonic; do
  echo "Compiling ${sketch} for ${FQBN}"
  arduino-cli compile --fqbn "$FQBN" "$sketch"
done
