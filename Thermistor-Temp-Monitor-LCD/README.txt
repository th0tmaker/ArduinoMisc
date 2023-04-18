Project utilizes:

Arduino UNO microcontroller
Half-sized breadboard
Arduino IDE (2.X)

Circuit components:

- Alphanumeric LCD 16x2 (dot matrix) w/ blue backlight (HD44780)
- 10kΩ Potentiometer, linear taper w/ knob
- 4700Ω @ 25°C NTC Thermistor 
- 220Ω Resistor
- 4700Ω Resistor
- Solid core jump wires (+21x)
- Red & black jump wires (2x)
- Red & black wires + connector to hold the thermistor


READING THERMISTOR VALUE ON MICROCONTROLLER:


Voltage Divider Circuit (Rfix connected to VCC): 	

Formula:
Vout = Vin * (Rth / (Rth + Rfix)))
Rth = (Vout * Rfix) / (Vin - Vout)

      +5V
       |
	 |
      | |
	| |Rfix       
      |_|	
	 |    
       |
	 |
       o-------- Vout (Analog input)
	 |
	 |
     | |
     \| |
	|\|Rth (Thermistor)       
      |_|\	
	 |
	 |      
	GND


Voltage Divider Circuit (Rfix connected to GND):

Formula:
Vout = Vin * (Rfix / (Rth + Rfix))
Rth = Rfix * (Vin / Vout - 1)

      +5V
       |
     | |
     \| |
	|\|Rth (Thermistor)       
      |_|\	
	 |    
       |
	 |
       o-------- Vout (Analog input)
	 |
	 |
     	 |
      | |
	| |Rfix    
      |_|	
	 |
	 |      
	GND


Description:

A makeshift thermometer that uses a NTC thermistor as the basis to measure temperature in Celsius in relation its resistance. Both, the temperature in Celsius and the thermistor's resistance are displayed on the Arduino's internal serial monitor, as well as an external LCD screen that displays the data and updates the readings every second.  

The wiring instructions for the LCD parallel interface connection are the following:

1. VSS: (Ground) - This pin is connected to ground.

2. VDD: (+5V) - This pin is connected to a 5V power source.

3. V0: (Contrast) - This pin is connected to the middle pin (wiper) o a potentiometer (variable resistor) to adjust the contrast of the display.

4. RS: (Register Select) - This pin is connected to a digital pin in order to select between the data register (when RS=0) and the command register (when RS=1).

5. RW: (Read/Write) - This pin is used to control the direction of data transfer between the microcontroller and the LCD module. The pin is connected to ground in order to WRITE data to the LCD. If you want to READ data from your LCD, connect this pin to the power source. 

6. E: (Enable) - This pin is connected to a digital pin on the Arduino and is used to signal the LCD module when data is ready to be read or written.

7. DB0-DB7: (Data Bus) - These pins are used to transmit data to/from the microcontroller. In this project, only 4 data buses are used to save on extra wires. For a faster data transfer you can wire all 8 data buses into their respective digital pin on the Arduino. 

8. A: (Anode) - This pin is used to control the backlight of the LCD module. Connect it to a +5V power source in series with a resistor (projects uses a 220 ohm THT resistor). 

9. K: (Cathode) - This pin is also used to control the backlight of the LCD module. Connect it to ground.

After connecting and wiring the LCD module, the code includes the <LiquidCrystal.h> library for working with the LCD display. The pins connected from the LCD to the Arduino (RS, E, D4, D5, D6, D7) are defined in the code and the liquid crystal display is initialized in the void setup() by using lcd.begin(16, 2);... Likewise, the serial monitor in the Arduino IDE is also initialized using: Serial.begin, with a baud rate of 9600) to monitor the program's output from the software itself. 

The program's code is written to measure the temperature of a thermistor using a voltage divider circuit and the Steinhart-Hart equation. The thermistor is connected to an analog pin (A0) on an Arduino board and a fixed resistor (Rfix) through GND to form a voltage divider circuit. The output voltage from the voltage divider circuit is then firstly measured, then scaled back to a comparative 0-5V ratio and used to calculate the resistance value of the thermistor, which is then plugged into the Steinhart-Hart equation to calculate the temperature in Celsius. In thermodynamics, the common unit of temperature measurement is Kelvin, which is why the final output of the Steinhart-Hart equation is temperature measured in Kelvins. An extra step is added to translate the temperature into a more practical, human-friendly way of measuring relaying temperature, which is done in degrees Celsius. This is achieved by substracting -273.15 from the final result we get from out Steinhart-Hart equation.  

The program needs several variables to perform these calculations. The thermistorPin variable is used to store the analog pin number to which the thermistor is connected. The Vin variable is used to store the power supply input voltage (5V). The Vout variable stores the voltage output from the voltage divider circuit. The thValADC variable stores the analog signal from the thermistor converted into 8-bit digital format (0, 1023).

The Rth variable stores the resistance value of the thermistor calculated using the voltage output (Vout) and the fixed resistor value (Rfix). The Rref variable stores the resistance value of the thermistor at a reference temperature of 25°C. The a1, b1, c1, and d1 variables store the Steinhart-Hart coefficients used in the Steinhart-Hart equation.

The setup() function initializes the serial monitor and the LCD display. The loop() function reads the analog signal voltage from the thermistor, scales it to a range between 0 and 5V, and uses it to calculate the resistance value of the thermistor. The Steinhart-Hart equation is then used to calculate the temperature in Celsius, which is displayed on the LCD display. The program also prints the thermistor resistance value and temperature value on the serial monitor for debugging purposes. The program then waits for one second before clearing the LCD display and starting the loop again.

Overall, this program provides an accurate and efficient way to measure and monitor the temperature and resistance of a thermistor using a voltage divider circuit and the Steinhart-Hart equation.