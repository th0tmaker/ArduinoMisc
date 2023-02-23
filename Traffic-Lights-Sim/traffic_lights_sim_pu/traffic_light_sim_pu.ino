// Pin definitions
const int RED_PIN = 13;
const int YELLOW_PIN = 12;
const int GREEN_PIN = 11;
const int BUTTON_PIN = 2;

// Timing constants (in milliseconds)
const int RED_TIME = 5000;
const int YELLOW_TIME = 2000;
const int GREEN_TIME = 5000;
const int DEBOUNCE_DELAY = 200;

// State variables
int state = 0;  // 0 = inactive, 1 = cycling, 2 = off
unsigned long lastButtonTime = 0; // store last time button was pressed
bool buttonPressed = false;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // enable the internal pull-up resistor
}

void loop() {
  // Check for button press with debounce
  unsigned long now = millis(); // track time
  if (now - lastButtonTime > DEBOUNCE_DELAY) {
    bool buttonState = digitalRead(BUTTON_PIN);
    if (buttonState == LOW && !buttonPressed) {
      buttonPressed = true;
      lastButtonTime = now;
      if (state == 0) {
        state = 1;
      } else if (state == 1) {
        state = 2;
      } else if (state == 2) {
        state = 1;
      }
    } else if (buttonState == HIGH) {
      buttonPressed = false;
    }
  }
  
  // Update the lights based on the current state
  if (state == 0) {
    // Lights are off
    digitalWrite(RED_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
  } else if (state == 1) {
    // Lights are cycling
    if (now % 14000 < RED_TIME) {
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(YELLOW_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
    } else if (now % 14000 < RED_TIME + YELLOW_TIME) {
      digitalWrite(RED_PIN, LOW);
      digitalWrite(YELLOW_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);
    } else if (now % 14000 < RED_TIME + YELLOW_TIME + GREEN_TIME) {
      digitalWrite(RED_PIN, LOW);
      digitalWrite(YELLOW_PIN, LOW);
      digitalWrite(GREEN_PIN, HIGH);
    } else if (now % 14000 < RED_TIME + YELLOW_TIME + GREEN_TIME + YELLOW_TIME) {
      digitalWrite(RED_PIN, LOW);
      digitalWrite(YELLOW_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);
    }
  } else {
    // Lights are off
    digitalWrite(RED_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
  }
}




