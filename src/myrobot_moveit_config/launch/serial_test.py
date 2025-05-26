import serial
ser = serial.Serial('/dev/ttyUSB1', 57600)
print("Connected!")
ser.close()
