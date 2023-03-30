#include <LiquidCrystal.h>

// initialize LiquidCrystal and define the pins
LiquidCrystal lcd(8, 7, 5, 4, 3, 2); // LiquidCrystal(rs=8, e=7, d4=5, d5=4, d6=3, d7=2)

// define LED pins
const int redLedPin = 12; // red LED pin
const int greenLedPin = 13; // green LED pin

// define countdown timer
const int timerStartVal = 30; // starting timer value
int timerCurrentVal = timerStartVal; // current timer value

// define intervals & delays
const int scrollInterval = 750; // scroll LCD display every 0.75 sec
const int decrementInterval = 1000; // decrement timer by 1 sec

// define LED state
unsigned long ledPreviousTime = 0; // previous time LED state was changed
const long ledBlinkInterval = 500; // interval for blinking red LED
bool ledState = false; // define initial LED state as False

enum LedStates { OFF, ON, BLINKING }; // an enumeration of the possible LED states
LedStates redLedState = OFF; // red LED starting state is OFF


void setup() {
  // LED pins setup
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
}

void loop() {
  lcd.begin(16, 2); // initialize lcd display setup
  lcd.print("Countdown: ");
  lcd.setCursor(11, 0);
  if (timerCurrentVal < 10) {
    // print num < 10 with "0" in front 
    lcd.print("0");
    lcd.print(timerCurrentVal);
  } else {
    lcd.print(timerCurrentVal);
  }


  // if current timer value is between 20 and 10:
  if (timerCurrentVal < 20 && timerCurrentVal >= 10) {
    redLedState = ON; // red LED is high
  }

  // if current timer value is between 10 and 0:
  if (timerCurrentVal < 10 && timerCurrentVal > 0) {
    redLedState = BLINKING; // red LED is blinking 
  }

  // if current timer value is equal to 0
  if (timerCurrentVal == 0) {
    redLedState = OFF; // red LED state OFF
    digitalWrite(redLedPin, LOW); // red LED is off
    digitalWrite(greenLedPin, HIGH); // green LED is on

    // print end message after timer hits 0
    lcd.clear();
    lcd.setCursor(5, 0); // top row message
    lcd.print("MEMORY");
    lcd.setCursor(5, 1);
    lcd.print("ERASED"); // bottom row message

    // for every character in LCD row
    for (int c = 0; c < 16; c++) {
      lcd.scrollDisplayRight(); // scroll display screen right
      delay(scrollInterval);
    }

    // reset current timer value back to starting timer value
    timerCurrentVal = (timerStartVal + 1);
    digitalWrite(greenLedPin, LOW);
  }
  
  // update LED state based on the current time and blink interval
  switch (redLedState) {
    case OFF:
      digitalWrite(redLedPin, LOW); // LED off
      break;
    case ON:
      digitalWrite(redLedPin, HIGH); // LED on
      break;
    case BLINKING:
      // initiate current time in ms to control LED blinking seperate from countdown timer
      unsigned long currentTime = millis();
      // when currentTime - ledPreviousTime are greater or equal than 0.5 sec 
      if (currentTime - ledPreviousTime >= ledBlinkInterval) {
        ledPreviousTime = currentTime;
        ledState = !ledState; // switch LED state to false
        digitalWrite(redLedPin, ledState); // write state to red LED
      }
      break;
  }

  // decrement current timer value by -1 every second
  timerCurrentVal--;
  delay(decrementInterval);
}
