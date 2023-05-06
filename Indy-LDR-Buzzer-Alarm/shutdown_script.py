import serial

srl = serial.Serial('COM4', 9600)  # port="COM4", baud rate=9600 <- change port/baud rate if need be
srl.write(b"q")  # write string "q" into byte format
srl.close()  # close serial connection
