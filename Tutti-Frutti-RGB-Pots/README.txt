Project utilizes:

Arduino UNO microcontroller
Half-sized breadboard
Arduino IDE (2.X)

Circuit components:

- RGB LED, 5mm, common cathode
- 10k Ω Potentiometer, linear taper w/ knob (3x)
- 220 Ω Resistor (3x)
- Solid core jump wires (13x)
- red & black jump wires (2x)

Description:

In this project we created a demonstration example of how to adjust the value of seperate colors (red, green, blue) in an RGB LED by using a potentiometer to control the intensity for each individual color. By doing so, we can use each of the three potentiometers to manually control the amount of intensity we get from either the red, green or blue color, which allows us to mix together different values of these colors in order to achieve a wider range of different colors. 

The program first defines all the pins for our RGB LED and our potentiometers that we will use. After that it handles the setup() by writing each RGB pin individually as an output. Next, the analogRead() function is used to read the values from each potentiometer, which in our case with total resistance 10k Ω potentiometers, range from 0 to 1023. It then maps these values read from the potentiometers to a range of 0 to 255, which is the range that can be written to the PWM (pulse-width modulation) pins that control the intensity of the LED.

To use this program, connect the RGB diode's pins to their designated PWM acceptable pins on the microcontroller board. While doing so, don't forget to pass each pin of the RGB LED through a resistor (220-330 Ω typically). To use the potentiometers, wire each of their wipers (middle pin) to the corresponding analog pin on the Arduino. The outside two pins are connected; one to ground and the other to the voltage power supply. Which one of the two goes where will determine how your signal will be read (either clockwise or counter-clockwise to increase the value). After you're done with the wiring and assembly, upload the code to the board and adjust the potentiometers to change the LED's color.