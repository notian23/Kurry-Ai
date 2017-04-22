#!/usr/bin/env python3
import aiml
import os
import sys
import serial
import time

# Aiml
kury = aiml.Kernel()

running = True

class main():
  
  def init(self):
    #Initalize voice
    print("Main: Stating Services")

    print("Main: Starting Voice")
      
    print("Main: Starting Web Gui")
    #os.system("cd Services/Server && python -m SimpleHTTPServer 8000")
    print("Main: Starting AIML")
    kury.learn("Services/Brain/Chatbot/bot.aiml")
    print("Main: Connecting to arduino")
    usbport = "COM3"
    
    try:
        right_arduino = serial.Serial(usbport, 9600)

    except:
        print("Could not connect to arduino on port " + usbport)
    
    usbport = "COM4"

    try:
        right_arduino = serial.Serial(usbport, 9600)

    except:
        print("Could not connect to arduino on port " + usbport)

core = main()

core.init()

while running == True:
  message =  kury.respond(raw_input("User >> "))
  print("Kury >> " + kury.respond(message))
