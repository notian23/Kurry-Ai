#!/usr/bin/env python3
import aiml
import os
import serial

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
    #kury.learn("Services/Brain/Chatbot/bot.aiml")
    print("Main: Connecting to arduino")
    try:
        Left_Arduino = serial.Serial("COM3", 9600)
        Right_Arduino = serial.Serial("COM4", 9600)
    except:
        print("Could not connect to arduino")

core = main()

core.init()

while running == True:
  message =  kury.respond(raw_input("User >> "))
  print("Kury >> " + kury.respond(message))
