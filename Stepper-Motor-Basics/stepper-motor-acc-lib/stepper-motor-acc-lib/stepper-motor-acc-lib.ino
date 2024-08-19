#include <AccelStepper.h>

#define IN1_PIN 11
#define IN2_PIN 10
#define IN3_PIN 9
#define IN4_PIN 8

const int stepsPerRevolution = 2048;  // number of steps for one full rotation (360°)  
const int maxSpeed = 800;  // maximum speed in steps per second
const int acceleration = 6;  // acceleration in steps per second^2

// Create an instance of the AccelStepper class with FULL4WIRE mode for 4-wire unipolar stepper motor (pin order important!)
AccelStepper myStepper(AccelStepper::FULL4WIRE, IN1_PIN, IN3_PIN, IN2_PIN, IN4_PIN);

void setup() {
  myStepper.setMaxSpeed(maxSpeed);
  myStepper.setAcceleration(acceleration);
}

void loop() {
  // Update current motor shaft position to zero at the start of each loop iteration
  myStepper.setCurrentPosition(0);

  // Rotate clockwise for one full revolution
  myStepper.moveTo(stepsPerRevolution);  // set target position for one full revolution
  while (myStepper.distanceToGo() != 0) {
    myStepper.run();
  }

  // Pause between changing direction
  delay(3000);

  // Update current motor shaft position to zero at the start of each loop iteration
  myStepper.setCurrentPosition(0);

  // Rotate counterclockwise for one full revolution
  myStepper.moveTo(-stepsPerRevolution);  // set target position for one full revolution counterclockwise
  while (myStepper.distanceToGo() != 0) {
    myStepper.run();
  }
}
