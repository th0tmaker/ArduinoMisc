Project utilizes:

Arduino UNO microcontroller
Half-sized breadboard
Arduino IDE (2.X)

Circuit components:

- Red LED
- Yellow LED
- Green LED
- Tactile Pushbutton
- 220 Ω Resistor (3x)
- 10k Ω Resistor 
- Solid core jump wires (10x)


Description:

This is a project that uses an Arduino UNO board to simulate the conventional traffic lights pattern.
The program begins by defining variables for pins, constants, and states that will be utilized throughout the program.
The setup and main loop are then handled, with the main loop primarily focused on monitoring for button input.
The program allows for the traffic lights to be toggled on and off via the pushbutton, while also establishing the correct desired traffic lights pattern.
Time tracking is deployed to add a debounce delay to the button, ensuring that the button signal is consistently being registered.
To achieve this, an external pull-down 10k Ω resistor is wired to the button on the breadboard to make sure the signal is registered as LOW voltage when unpressed.