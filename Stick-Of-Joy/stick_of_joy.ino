int VRx = A0; // Joystick X-axis
int VRy = A1; // Joystick Y-axis
int BTN = 2;  // Joystick button
int xVal;  // X-axis value
int yVal;  // Y-axis value
int btnState; // Button state
const int centerVal = 512; // Define the center positional value of the joystick 
const int threshold = 50;  // Adjust this value based on joystick sensitivity
String dir = "";

void setup() {
  Serial.begin(9600); // Start the serial communication
  pinMode(BTN, INPUT_PULLUP); // Enable internal pull-up resistor for the button

}

void loop() {
  int xVal = analogRead(VRx);  // Read X-axis value
  int yVal = analogRead(VRy);  // Read Y-axis value
  int btnState = digitalRead(BTN); // Read button state

  int xDev = xVal - centerVal; // Calculate X-axis deviation from center position
  int yDev = yVal - centerVal; // Calculate Y-axis deviation from center position

  int absXDev = abs(xDev); // Get absolute values of X-axis deviation
  int absYDev = abs(yDev); // Get absolute values of Y-axis deviation

  // If either the X-axis or Y-axis deviation is greater than the defined threshold, the joystick is considered to be moved away from the center position
  if (absXDev > threshold || absYDev> threshold) {
    
    // If the X-axis deviation is greater than the Y-axis deviation (horizontal joystick movement is dominant)
    if (absXDev > absYDev) {

      // If X-axis deviation is LESSER than 0, direction = LEFT
      if (xDev < 0) {
        dir = "Left";

      // Else X-axis deviation is GREATER than 0, direction = RIGHT
      } else {
        dir = "Right";
      }

    // If the Y-axis deviation is greater than the X-axis deviation (vertical joystick movement is dominant)
    } else {

      // If Y-axis deviation is LESSER than 0, direction = UP
      if (yDev < 0) {
        dir = "Up";

      // Else Y-axis deviation is GREATER than 0, direction = DOWN
      } else {
        dir = "Down";
      }
    }

  // If none of the conditions are met, joystick is at its center position
  } else {
    dir = "Center";
  }

  // Print the direction and button state to the Serial Monitor (the output will be used as a source to extract info with another language)
  Serial.println("Direction: " + dir + " | Button: " + (btnState == LOW ? "1" : "0"));
  delay(5);
}