// Define the pins for the RGB LED
const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

// Define the pins for the potentiometers
const int redPotPin = A1;
const int greenPotPin = A2;
const int bluePotPin = A3;

void setup() {
  // Set the LED pins as outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // Read the input values from the potentiometers (0, 1023)
  // Use map() to match the values with the 8bit res PWM values (0 255) using linear interpolation
  int redVal = map(analogRead(redPotPin), 0, 1023, 0, 255);
  int greenVal = map(analogRead(greenPotPin), 0, 1023, 0, 255);
  int blueVal = map(analogRead(bluePotPin), 0, 1023, 0, 255);

  // Set the RGB LED to the new values
  analogWrite(redPin, redVal);
  analogWrite(greenPin, greenVal);
  analogWrite(bluePin, blueVal);
  
  // Short delay before repeating the loop
  delay(20);