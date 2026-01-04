const int pwmPin = 11;   // PWM
const int dirPin = 8;    // DIR
const int potPin = A0;   // Potentiometer pin
const int btnPin = 2;    // Button to GND


bool lastBtnReading = HIGH;
bool btnState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceMs = 40;

void setup() {
  pinMode(pwmPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);

  // Initial direction
  digitalWrite(dirPin, HIGH);
}

void loop() {
  // Read value 0-1023 and map to PWM range 0-255
  int potValue = analogRead(potPin);
  int motorSpeed = map(potValue, 0, 1023, 0, 255);

  analogWrite(pwmPin, motorSpeed);

  // button direction
  bool reading = digitalRead(btnPin);

  if (reading != lastBtnReading) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceMs) {
    if (reading != btnState) {
      btnState = reading;

      if (btnState == LOW) { 
        analogWrite(pwmPin, 0);
        delay(150);

        //change direction
        digitalWrite(dirPin, !digitalRead(dirPin));
      }
    }
  }

  lastBtnReading = reading;
}
