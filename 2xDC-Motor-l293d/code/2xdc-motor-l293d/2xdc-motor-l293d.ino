const int IN1 = 12; // Digital pin connected to IN1 for M1
const int IN2 = 11; // Digital pin connected to IN2 for M1
const int IN3 = 8;  // Digital pin connected to IN3 for M2
const int IN4 = 7;  // Digital pin connected to IN4 for M2

const int potM1Pin = A5; // Analog pin connected to potentiometer for Motor 1 (M1)
const int EnAPin = 10;   // PWM pin connected to EN-A of L293D
const int EnBPin = 9;    // PWM pin connected to EN-B of L293D

// Declare global variables
int potM1Val;  // Store potentiometer value (0-1023)
int EnApwmVal; // Store PWM value (0-255)
int EnBpwmVal; // Store PWM value (0-255)

// Timing variables (integers)
unsigned long M2prevDirChange = 0; // Store Motor 2 previous direction change
unsigned long M2prevDirDelay = 0;  // Store Motor 2 previous direction delay
const long M2spinInterval = 2000;  // Interval defining how long Motor 2 is spinning
const long M2dirDelay = 1000;      // Delay before Motor 2 changes its direction

// Timing variables (booleans)
bool M2dirForward = true; // Motor 2 direction is forward
bool M2changeReverse = false;   // Flag to track if Motor 2 is looking to change its direction into reverse
bool M2dirChangeDelayActive = false; // Flag to track if delay timer for Motor 2 is active (not spinning)

void setup() {
  // Set all IN of L293D pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Set the EN-A & EN-B pin of L293D as output
  pinMode(EnAPin, OUTPUT);
  pinMode(EnBPin, OUTPUT);
}

void loop() {
  // Update potentiometer and PWM values in each loop iteration
  potM1Val = analogRead(potM1Pin);             // Read potentiometer value (0-1023)
  EnApwmVal = map(potM1Val, 0, 1023, 0, 255);  // Map to 8-bit PWM range for M1 (0-255)
  EnBpwmVal = 0;                               // Set a fixed PWM value for M2 (0-255)
  
  analogWrite(EnAPin, EnApwmVal); // Output PWM signal based on potentiometer to Motor 1 driver
  analogWrite(EnBPin, EnBpwmVal); // Output fixed PWM value to Motor 2 driver
    
  //For Motor 1 (IN1 and IN2), for Motor 2 (IN3 and IN4):
  //Forward: IN1 = HIGH, IN2 = LOW
  //Reverse: IN1 = LOW, IN2 = HIGH
  //Coast (Inertia into Stop): IN1 = LOW, IN2 = LOW
  //Brake (Quick Stop): IN1 = HIGH, IN2 = HIGH

  // Control Motor 1 (M1):
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Control Motor 2 (M2):
  unsigned long currMs = millis(); // Init timer in milliseconds and store current ms in a variable 

  // If Motor 2 is not looking to change its direction into reverse and time elapsed since its last direction change (currMs - M2prevDirChange) is greater than its spin interval
  if (!M2changeReverse && (currMs - M2prevDirChange >= M2spinInterval)) {
    M2prevDirDelay = currMs;         // Update previous direction delay timer with current timer
    M2changeReverse = true;          // Spin interval expired, set change direction into reverse flag as true
    M2dirChangeDelayActive = true;   // Set direction change delay active to stop the motor
  }

  // If Motor 2 is looking to change its direction into reverse and time elapsed since its last delay (currMs - M2prevDirDelay) is greater than its delay timer
  if (M2changeReverse && (currMs - M2prevDirDelay >= M2dirDelay)) {
    M2dirForward = !M2dirForward;      // Change Motor 2 direction to reverse after delay timer
    M2prevDirChange = currMs;          // Update previous direction delay timer with current timer
    M2changeReverse = false;           // Spin interval expired, set change direction into reverse flag as true
    M2dirChangeDelayActive = false;    // End the delay period
  }
  

  // Set Motor 2 direction based on its state, or stop during delay
  if (M2dirChangeDelayActive) {
    // During the delay, stop Motor 2 (set both inputs LOW)
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  } else if (EnBpwmVal > 0) {
    // Normal operation: Set Motor 2 direction
    if (M2dirForward) {
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW); // Forward direction
    } else {
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH); // Reverse direction
    }
  } else {
    // Stop Motor 2 if its PWM value is 0
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}