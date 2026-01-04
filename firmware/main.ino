// Cytron motor control pins
const int pwmPin = 11;   // PW1
const int dirPin = 8;    // DIR
const int btnPin = 2;    // button to GND

// Speed value (0–255)
const int motorSpeed = 255;

// Debounce variables
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

  
  analogWrite(pwmPin, motorSpeed);
}

void loop() {
  bool reading = digitalRead(btnPin);

  if (reading != lastBtnReading) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceMs) {
    if (reading != btnState) {
      btnState = reading;

      // Button pressed (LOW)
      if (btnState == LOW) {
        // Stop briefly
        analogWrite(pwmPin, 0);
        delay(150);

        // Flip direction pin directly
        digitalWrite(dirPin, !digitalRead(dirPin));

        // Resume motor
        analogWrite(pwmPin, motorSpeed);
      }
    }
  }

  lastBtnReading = reading;
}
