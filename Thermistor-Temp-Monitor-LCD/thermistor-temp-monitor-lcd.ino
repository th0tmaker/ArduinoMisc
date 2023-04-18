#include <LiquidCrystal.h>

// initialize LiquidCrystal and define the pins
LiquidCrystal lcd(8, 7, 5, 4, 3, 2); // LiquidCrystal(rs=8, e=7, d4=5, d5=4, d6=3, d7=2)

int thermistorPin = A0; // analog signal from the thermistor via analog pin A0
const float Vin = 5.0; // power supply input voltage
float Vout; // output voltage from a voltage divider circuit consisting of a thermistor and a fixed series resistor
float thValADC; // variable keeping track of the thermistor current analog signal converted into 8bit (0, 1023) digital format 
float Rth, tempKelvin, tempCelsius; // Rth = thermistor resistance, tempKelvin = temperature in Kelvin, tempCelsius = temperature in Celsius
float Rfix = 4700.0; // fixed series resistor value used in a voltage divider circuit
float Rref = 4700.0; // resistor value of thermistor at reference temperature 25°C
float a1 = 3.354016e-03, b1 = 2.569850e-04, c1 = 2.620131e-06, d1 = 6.383091e-08; // Steinhart-Hart coefficients for temperature calculation

void setup() {
  Serial.begin(9600); // initialize serial monitor
  lcd.begin(16, 2); // initialize lcd display setup
}

void loop() {
  //  Reads analog signal voltage (0V to 5V) and converts it into a digital value (0 to 1023)
  thValADC = analogRead(thermistorPin);
  
  // Scale the digital value (0, 1023) to a range between 0 and 5 to better represent a voltage ouput
  // Now it is easier to use the voltage divider circuit formula to calculate the resistance
  Vout = (Vin * thValADC) / 1023.0; // Vout = (Vin * ADCvalue) / 1023

  // Vout = Vin * (Rth / (Rth + Rfix)) -> fixed series R to VCC pin config
  //    Rth = (Vout * Rfix) / (Vin - Vout) 
  // Vout = Vin * (Rfix / (Rth + Rfix)) -> fixed series R to GND pin config
  //    Rth = Rfix * (Vin / Vout - 1)

  // Calculate resistance value of the thermistor using voltage going across it (Vout) and the fixed series resistor (Rfix) connected to GND instead of 5V
  Rth = Rfix * (Vin / Vout - 1); 

  // Steinhart-Hart equation with FOUR (a1,b1,c1,d1) coefficients to calculate temperature in Kelvin:
  tempKelvin = 1.0 / (a1 + (b1 * (log(Rth / Rref))) + (c1 * pow(log(Rth / Rref), 2.0)) + (d1 * pow(log(Rth / Rref), 3.0))); // 1/T= a1 + b1*ln(Rth/Rref) + c1*ln(Rth/Rref)^2 + d1*ln(Rth/Rref)^3
  tempCelsius = tempKelvin - 273.15; // translate temperature from Kelvin into Celsius
  

  // print thermistor resistance value on serial monitor
  Serial.print("Thermistor Resistance = ");
  Serial.print(Rth);
  Serial.println(" ohms");
  
  // print temperature value on serial monitor
  Serial.print("Temperature = ");
  Serial.print(tempCelsius);
  Serial.println(" C");

  // display temperature value on LCD display
  lcd.setCursor(0, 0); // set cursor to the first row
  lcd.print("Temp = ");
  lcd.print(tempCelsius);   
  lcd.print(" C");

  // display thermistor resistance value on LCD display
  lcd.setCursor(0, 1); // set cursor to the second row
  lcd.print("R = ");
  lcd.print(Rth);
  lcd.print(" ohms");
  
  delay(1000);  // wait 1 second before updating display with data     
  lcd.clear(); // clear lcd contents after every cycle
}