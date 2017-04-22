import serial

usbport = "COM4"

class Right_Arduino:

    def connect(self):
        try:
            right_arduino = serial.Serial(usbport, 9600)

        except:
            print("Could not connect to arduino on port " + usbport)
