// pin definitions
int ldrPin = A5;
int redLedPin = 12;
int buzzerPin = 11;
int buttonPin = 10;

// musical notes and their corresponding frequencies
long C=523.25,
D=587.33,
E=659.26,
F=698.46,
G=783.99,
A=880,
B=987.77,
C2=1046.50,
D2=1174.66,
E2=1318.51,
F2=1396.91,
ZERO=0;

// Defining the duration of musical notes: five-beat=1000, four-and-half-beat=900, whole note=800, half note=400, quarter note=200, eighth note=100
int fb=1000, fhb=900, b=800, n=400, c=200, s=100;

// Creating the melody theme by putting musical notes in correct order (current theme: Indiana Jones: 'Raiders March')
long melodyTheme[] = {E,F,G,C2,
                 D,E,F,
                 ZERO,
                 G,A,B,F2,
                 A,B,C2,D2,E2,
                 E,F,G,C2,
                 D2,E2,F2,
                 G,G,E2,D2,G,
                 E2,D2,G,
                 E2,D2,G,
                 F2,E2,D2,C,
                 E,G,F,
                 D,F,E,G,
                 C,C,E,G,F,
                 D,F,E,D,
                 C,C,E,G,F,
                 D,F,E,G,
                 C,C,G,G,
                 E2,D2,G,
                 E2,D2,G,
                 E2,D2,G,
                 F2,E2,D2,C,
                 ZERO
                };

int noteDurations[] = {n,s,n,b, // duration of each note in the melody
                       c,c,fb,
                       c,
                       n,s,n,fhb,
                       c,c,n,n,
                       n,c,c,n,
                       b,c,c,b,
                       c,c,n,
                       c,c,n,
                       c,c,n,
                       c,c,n,
                       c,c,b,
                       c,c,b,
                       c,c,s,s,c,
                       b,c,c,b,
                       c,c,s,s,c,b,
                       c,c,b,
                       c,c,s,s,c,
                       b,c,c,n,
                       c,c,n,
                       c,c,n,
                       c,c,n,
                       c,c,fb,
                       b
                      };

// melody variables
int melodyPos = 0;
bool melodyPlaying = false;

// button variables
bool buttonState = false;
bool prevButtonState = false;
unsigned long lastButtonPress = 0;
unsigned long debounceDelay = 50;

// note variables
unsigned long noteStartTime = 0;
unsigned long noteInterval = 0;

void setup() {
  // pinMode(ldrPin, INPUT); -> automatically defined as it can only have 'INPUT' mode
  pinMode(redLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600); // initialize serial monitor for display and communication
  
}

void loop() {
  // read button input and save into buttonState
  buttonState = digitalRead(buttonPin);
  
  if (buttonState != prevButtonState) { // check if button state has changed, not same as prevButtonState
    if (buttonState == LOW) { // internal pull-up configurationn ('unpressed' button = HIGH, 'pressed' button = LOW)
      unsigned long now = millis(); // track time
      if (now - lastButtonPress > debounceDelay) { // check if debouncing delay has elapsed
        lastButtonPress = now;
        // if melody is not playing, start playing from beginning
        if (!melodyPlaying) { 
          melodyPos = 0; // set melody position to start
          melodyPlaying = true; // melody is active
          // if melody is playing, rewind to beginning and stop playing
        } else {
          melodyPos = 0; // set melody position to start
          noteStartTime = 0; // Reset note start time to zero (to avoid first two tones being played improperly)
           melodyPlaying = false; // melody is inactive
          noTone(buzzerPin); // stop playing notes from buzzer
        }
      }
    }
    // buttonState becomes prevButtonState to contrast it against new buttonState when button is pressed again
    prevButtonState = buttonState;
  }
  // if melody is active
  if (melodyPlaying) {
    // read LDR value and save into LdrValADC 
    int ldrValADC = analogRead(ldrPin);
    // print LDR value on screen
    Serial.print("LDR value: ");
    Serial.println(ldrValADC);

    // if LDR value is greater than 10
    if (ldrValADC > 100) {
      melodyPlaying = false; // melody is inactive
      noTone(buzzerPin); // stop playing notes from buzzer

      // sound alarm and blink red LED indefinitely (only way to stop is by clicking 'RESET' button on Arduino or turning power OFF)
      while (true) {
        tone(buzzerPin, 1000, 200); // play a 1000 Hz tone for 200 ms
        digitalWrite(redLedPin, HIGH);
        delay(200);
        digitalWrite(redLedPin, LOW);
        noTone(buzzerPin);
        delay(200);

      }
    } 
    if (noteStartTime == 0) { // if a new note is starting
      noteInterval = noteDurations[melodyPos]; 
      if (melodyTheme[melodyPos] != ZERO) { // if the note is not a rest
        tone(buzzerPin, melodyTheme[melodyPos]); // start playing the note
      }
      noteStartTime = millis(); // record the start time of the note
    } else if (millis() - noteStartTime >= noteInterval) { // if the duration of the note has elapsed
      noTone(buzzerPin); // stop playing the note
      noteStartTime = 0; // reset the start time of the note
      melodyPos++; // increment melody position to move to the next note in the melody theme
      
      if (melodyPos == sizeof(melodyTheme)/sizeof(melodyTheme[0])) { // if end of melody is reached, rewind to beginning and stop playing
        melodyPos = 0; // set melody position to start
        melodyPlaying = false; // melody is inactive
        noTone(buzzerPin); // stop playing notes from buzzer
        delay(500); // add a short delay here to allow the last tone to complete playing
      }
    }
  }
  // turn off program via Python script (Serial monitor inside Arduino IDE NEEDS to be closed)
  if (Serial.available() > 0) {
        char incomingByte = Serial.read();
    if (incomingByte == 'q') {
      melodyPos = 0; // set melody position to start
      melodyPlaying = false; // melody is inactive
      noTone(buzzerPin); // stop playing notes from buzzer
      digitalWrite(redLedPin, LOW); // turn red LED OFF
      delay(100);
    }
  }
}