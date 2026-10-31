// Lab 03: classroom light/thermistor voltage threshold alarm.
// These are VOLTAGE thresholds, not a calibrated temperature in Celsius.
// RGB LED assumed common-anode (LOW means on).

const byte LIGHT_SENSOR_PIN = A0;
const byte THERMISTOR_PIN = A1;
const byte GREEN_LED_PIN = 11;
const byte RED_LED_PIN = 12;
const byte BUZZER_PIN = A8;
const float ADC_REFERENCE_V = 5.0f;  // Arduino Mega default analog reference.
const float LIGHT_LOW_V = 1.0f;
const float LIGHT_HIGH_V = 3.5f;
const float TEMP_LOW_V = 2.5f;
const float TEMP_HIGH_V = 3.0f;

void setup() {
  Serial.begin(9600);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, HIGH);
  noTone(BUZZER_PIN);
}

void loop() {
  const float lightV = analogRead(LIGHT_SENSOR_PIN) * ADC_REFERENCE_V / 1023.0f;
  const float thermistorV = analogRead(THERMISTOR_PIN) * ADC_REFERENCE_V / 1023.0f;
  const bool lightAlert = lightV < LIGHT_LOW_V || lightV > LIGHT_HIGH_V;
  const bool tempAlert = thermistorV < TEMP_LOW_V || thermistorV > TEMP_HIGH_V;
  const bool anyAlert = lightAlert || tempAlert;

  digitalWrite(GREEN_LED_PIN, anyAlert ? HIGH : LOW);
  digitalWrite(RED_LED_PIN, anyAlert ? LOW : HIGH);
  if (lightAlert && tempAlert) tone(BUZZER_PIN, 2000);
  else noTone(BUZZER_PIN);

  Serial.print(F("Light_V:")); Serial.print(lightV, 2);
  Serial.print(F("\tThermistor_V:")); Serial.print(thermistorV, 2);
  Serial.print(F("\tState:"));
  if (lightAlert && tempAlert) Serial.println(F("BOTH_ALERT"));
  else if (lightAlert) Serial.println(F("LIGHT_ALERT"));
  else if (tempAlert) Serial.println(F("THERMISTOR_ALERT"));
  else Serial.println(F("NORMAL"));
  delay(200);
}
