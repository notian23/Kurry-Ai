import serial

arduino = serial.Serial('/dev/tty.usbserial', 9600)
while True:
    print arduino.readline()

