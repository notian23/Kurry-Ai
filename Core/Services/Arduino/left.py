import serial

usbport = "COM3"

class Left_Arduino:
    
    def connect(self):
        try:
            left_arduino = serial.Serial(usbport, 9600)

        except:
            print("Could not connect to arduino on port " + usbport)
