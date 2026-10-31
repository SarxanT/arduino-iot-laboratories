// Lab 01: four pushbuttons control a common-anode RGB LED.
// Refactored from the author's Arduino Mega coursework exercise.
// Common-anode LED: 0 = full on, 255 = off (PWM output is inverted).

const byte BUTTONS[] = {2, 3, 43, 44};
const byte RED_PIN = 12;
const byte GREEN_PIN = 11;
const byte BLUE_PIN = 10;
int previousSelection = -2;

void setColor(byte red, byte green, byte blue) {
  analogWrite(RED_PIN, 255 - red);
  analogWrite(GREEN_PIN, 255 - green);
  analogWrite(BLUE_PIN, 255 - blue);
}

void setup() {
  Serial.begin(9600);
  for (byte pin : BUTTONS) pinMode(pin, INPUT_PULLUP);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  setColor(0, 0, 0);
}

void loop() {
  int selection = -1;
  for (byte i = 0; i < 4; ++i) {
    if (digitalRead(BUTTONS[i]) == LOW) {
      selection = i;  // First pressed button wins if several are held.
      break;
    }
  }
  if (selection == previousSelection) return;
  delay(30);  // Simple debounce for this introductory lab.
  if (selection >= 0 && digitalRead(BUTTONS[selection]) != LOW) return;
  previousSelection = selection;

  switch (selection) {
    case 0: setColor(180, 0, 180); Serial.println(F("M1: Purple")); break;
    case 1: setColor(255, 0, 0); Serial.println(F("M2: Red")); break;
    case 2: setColor(255, 255, 255); Serial.println(F("M3: White")); break;
    case 3: setColor(64, 64, 64); Serial.println(F("M4: Dim white")); break;
    default: setColor(0, 0, 0); Serial.println(F("No button: LED off"));
  }
}
