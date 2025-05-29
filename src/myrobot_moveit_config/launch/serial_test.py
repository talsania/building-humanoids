import serial
ser = serial.Serial('/dev/ttyUSB0', 4000000)
print("Connected!")
ser.close()
