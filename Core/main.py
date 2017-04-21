#!/usr/bin/env python3
# Remember to install aiml using *** pip install aiml
import aiml
import os

# Debugging Purposes
from Gesture import *
 


# Scripts
# from Scripts import scriptExample

# Gestures Class's
# TODO: Remove this later
hand = Hand()
arm = Arm()
head = Head()

# Aiml
kurry = aiml.Kernel()
sessionId = 00001

# Speeding up load times
if os.path.isfile("Services/Voice/Chatbot/bot_brain.brn"):
  kurry.bootstrap(brainFile = "Services/Voice/Chatbot/bot_brain.brn")
else:
  kurry.bootstrap(learnFiles = "Services/Voice/Chatbot/Startup.aiml", commands = "load aiml")
  kurry.saveBrain("Services/Voice/Chatbot/bot_brain.brn")

class main():
  Version = '0.0.1'
  Author = 'Josh Brown'
  Email = 'Brownbear1002@gmail.com'
  
  def init():
    #Initalize voice
    print("Main: Stating Services")

    print("Main: Starting Voice")

    print("Main: Starting Web Gui")

    print("Main: Starting AIML")
    

while True:
  message =  kurry.respond(raw_input("Kurry >> "))

  if message == "quit" or "Quit":
    exit()

  elif message == "save" or "Save":
      kurry.saveBrain("Services/Voice/ChatBot/bot_brain.brn")
      bot_response = kernel.respond(message)
