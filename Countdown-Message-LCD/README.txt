Project utilizes:

Arduino UNO microcontroller
Half-sized breadboard
Arduino IDE (2.X)

Circuit components:

- Alphanumeric LCD 16x2 (dot matrix) w/ blue backlight (HD44780)
- Red LED, 5mm
- Green LED, 5mm
- 10kΩ Potentiometer, linear taper w/ knob
- 220 Ω Resistor (3x)
- Solid core jump wires (23x)
- red & black jump wires (2x)

Description:

This project uses the Arduino Uno and its corresponding language to showcase the program's output on an Alphanumeric, 16x2, dot-matric LCD screen. The code sets up timer starting at 30 seconds and starts counting down until it reaches 0. During the countdown, the red LED lights toggles through different states (either OFF, ON or BLINKING). Once the timer reaches zero the red LED turns OFF, while the green LED turns ON. As the green LED turns on, the LCD displays a pre-programmed message on the screen and starts scrolling it to the right every by one character space every 0.5 seconds. Once the message scrolls all the way off the screen, the program restarts back at the beginning.

As far as wiring was concerned, the project uses a parallel communication interface, meaning several wires have to be connected to their designated pins on the LCD module. Here's an overview of the wiring in an enumerated list format:

1. VSS: (Ground) - This pin is connected to ground.

2. VDD: (+5V) - This pin is connected to a 5V power source.

3. V0: (Contrast) - This pin is connected to the middle pin (wiper) o a potentiometer (variable resistor) to adjust the contrast of the display.

4. RS: (Register Select) - This pin is connected to a digital pin in order to select between the data register (when RS=0) and the command register (when RS=1).

5. RW: (Read/Write) - This pin is used to control the direction of data transfer between the microcontroller and the LCD module. The pin is connected to ground in order to WRITE data to the LCD. If you want to READ data from your LCD, connect this pin to the power source. 

6. E: (Enable) - This pin is connected to a digital pin on the Arduino and is used to signal the LCD module when data is ready to be read or written.

7. DB0-DB7: (Data Bus) - These pins are used to transmit data to/from the microcontroller. In this project, only 4 data buses are used to save on extra wires. For a faster data transfer you can wire all 8 data buses into their respective digital pin on the Arduino. 

8. A: (Anode) - This pin is used to control the backlight of the LCD module. Connect it to a +5V power source in series with a resistor (projects uses a 220 ohm THT resistor). 

9. K: (Cathode) - This pin is also used to control the backlight of the LCD module. Connect it to ground.

After connecting the LCD, LEDs, and potentiometer, the code includes the <LiquidCrystal.h> library for working with the LCD display. Then, the pins connected from the LCD to the Arduino (RS, E, D4, D5, D6, D7) are defined, and initial values are set for the timer, intervals, and LED states. In the setup function, the LED pins are initialized as output pins.

In the loop function, the program initializes the LCD display and prints the countdown timer value. It then checks the current value of the timer and updates the state of the red LED accordingly. If the timer value is between 20 and 10, the red LED is set to ON. If the timer value is between 10 and 0, the red LED is set to BLINKING. When the timer value is equal to 0, the red LED is set to OFF, and the green LED is turned ON. A message is displayed on the LCD screen in this state, before circling back to the start of the loop. This program will run continously while the power is on. 

The aim of this project was to specifically highlight the LCD component and it's usage in conjunction with a functioning timer while executing various LED operations simultaneously through the code's control flow as the timer counts down.