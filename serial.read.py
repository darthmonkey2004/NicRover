import logging
import sys
import serial
if sys.argv[1]:
	DEV = sys.argv[1]
else:
	DEV = "dev/ttyACM0"
if sys.argv[2]:
	BAUD = sys.argv[2]
else:
	BAUD = 115200
logging.basicConfig(filename='serialdata',level=logging.DEBUG)
ser = serial.Serial(DEV, BAUD)
while True:
	data = ser.readline()
	print data
	logging.debug(data)
