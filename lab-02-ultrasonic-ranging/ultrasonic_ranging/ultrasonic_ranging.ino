// Lab 02: distance measurement using an HC-SR04 ultrasonic sensor.
// Temperature is an assumed constant, NOT a reading from a sensor.

const byte TRIG_PIN = 48;
const byte ECHO_PIN = 8;
const float ASSUMED_TEMPERATURE_C = 23.5f;
const unsigned long ECHO_TIMEOUT_US = 30000UL;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  const unsigned long durationUs = pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT_US);
  if (durationUs == 0) {
    Serial.println(F("No echo (timed out)"));
  } else {
    const float speedOfSoundMetersPerSecond = 331.5f + 0.6f * ASSUMED_TEMPERATURE_C;
    const float distanceCm = durationUs * speedOfSoundMetersPerSecond / 20000.0f;
    Serial.print(F("Distance_cm:"));
    Serial.print(distanceCm, 1);
    Serial.print(F("\tDuration_us:"));
    Serial.println(durationUs);
  }
  delay(1000);
}
