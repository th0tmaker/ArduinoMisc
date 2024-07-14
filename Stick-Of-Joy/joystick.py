import serial
import logging
import time
import threading


class Joystick:
    def __init__(self, com_port='COM3', baud_rate=9600):
        self.com_port = com_port  # COM port for serial connection
        self.baud_rate = baud_rate  # baud rate for serial communication
        self.ser = None  # serial connection object, initially None
        self.direction = None  # variable to store joystick position translated into movement direction
        self.button_state = None  # variable to store button state
        self.thread = None  # thread object to handle asynchronous reading
        self.running = False  # flag to control the running state of the reading thread

    # This function sets up the serial communication between Python and the Arduino
    def setup_serial(self):
        # Attempt to open a serial connection with the specified COM port and baud rate
        try:
            self.ser = serial.Serial(self.com_port, self.baud_rate, timeout=1)
            logging.info(f"Successfully connected to {self.ser.portstr}")

        # If there is a serial connection error, log the error message.
        except serial.SerialException as e:
            logging.error(f"Error: {e}")
            self.ser = None  # set the serial connection object to None in case of an error

    # This function starts a separate thread to read joystick data
    def start_reading(self):
        # If a connection to the serial connection objects is established
        if self.ser and self.ser.isOpen():
            # Create a new thread to run the read_joystick_data method and start the thread
            self.thread = threading.Thread(target=self.read_joystick_data)
            self.thread.start()
            logging.info("Started reading joystick input in a separate thread.")
        else:
            logging.error(
                "Cannot start reading. Serial port not open.")

    # This function reads joystick data from the serial connection in a loop sequence
    def read_joystick_data(self):
        # If a connection to the serial connection objects is established
        if self.ser and self.ser.isOpen():
            self.running = True  # set the running flag to True to start the loop

            while self.running:
                try:
                    # Check if there is data waiting in the serial buffer
                    if self.ser.in_waiting > 0:
                        # Read a line from the serial port and decode it
                        line = self.ser.readline().decode('utf-8').strip()

                        # If no line is found, continue
                        if not line:
                            continue

                        # Check if the line contains direction and button state information
                        if line.startswith("Direction: ") and " | Button: " in line:
                            direction_start = len("Direction: ")  # calculate the start index of the direction
                            button_state_start = line.index(" | Button: ")  # find the start index of the button state

                            # Extract direction and button state from the line
                            self.direction = line[direction_start:button_state_start]
                            self.button_state = line[button_state_start + len(" | Button: "):]

                            # Log the extracted direction and button state
                            logging.info(f"Direction: {self.direction} | Button State: {self.button_state}")
                    else:
                        time.sleep(0.1)  # sleep briefly to avoid busy waiting

                except serial.SerialException as e:
                    logging.error(f"Serial error: {e}")
                    self.running = False  # Stop the loop on serial error

                except Exception as e:
                    logging.error(f"Unexpected error: {e}")
                    self.running = False  # Stop the loop on unexpected error
        else:
            logging.error("Serial port is not open or available")

    # This function stops a separate thread that reads joystick data
    def stop_reading(self):
        self.running = False  # set the running flag to False in order to stop the loop
        if self.thread:
            self.thread.join()  # wait for the reading thread to finish execution
            logging.info("Stopped reading joystick input and thread has been joined.")
            self.thread = None  # set the thread object to None

    # This function stops and closes the serial communication between Python and the Arduino
    def close_serial(self):
        if self.ser and self.ser.isOpen():
            self.ser.close()  # close the serial port
            logging.info("Serial port closed")
        else:
            logging.warning("Serial port is not open or was already closed")


# This function sets up and runs the joystick class
def main():
    # Configure logging to display info level messages and above
    logging.basicConfig(level=logging.INFO)
    joystick = Joystick()  # sreate a Joystick object
    joystick.setup_serial()  # set up the serial connection

    # If a connection to the joystick exists
    if joystick.ser:
        try:
            joystick.start_reading()  # start reading joystick data in a separate thread
            while True:
                time.sleep(0.5)  # main loop sleeps to keep the program running

        except KeyboardInterrupt:
            logging.info("Interrupted by user. Exiting...")  # log when the user interrupts the program

        finally:
            joystick.stop_reading()  # stop reading joystick data and join the thread
            joystick.close_serial()  # close the serial connection
    else:
        logging.error("Serial port setup failed. Exiting.")


if __name__ == "__main__":
    main()  # call the main function when the script is executed
