#include <Stepper.h>

#define IN1_PIN 11
#define IN2_PIN 10
#define IN3_PIN 9
#define IN4_PIN 8

const int stepsPerRevolution = 2048;  // number of steps for one full rotation (360°)
const int revolutionsPerMinute = 9;   // aka RPM, measure of how fast the motor is spinning

// Initialize the Stepper library with the pins connected to the motor (pin order important!)
Stepper myStepper(stepsPerRevolution, IN1_PIN, IN3_PIN, IN2_PIN, IN4_PIN);

void setup() {
  myStepper.setSpeed(revolutionsPerMinute);  // adjust the speed as needed
  Serial.begin(9600);  // initialize serial communication for debugging
}

void loop() {
  // Rotate clockwise in eights
  for (int i = 0; i < 8; i++) {
    Serial.println("Rotating Clockwise");
    myStepper.step(stepsPerRevolution / 8);  // rotate an eight revolution clockwise
    delay(2000);  // delay for 2 seconds between each iteration
  }

  // Rotate counterclockwise in full 
  Serial.println("Counterclockwise");
  myStepper.step(-stepsPerRevolution);  // rotate one full revolution counterclockwise
  delay(1000);  // delay for 1 second rotation is complete
}
