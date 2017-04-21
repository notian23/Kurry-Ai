#!/usr/bin/env python3
# Remember to install aiml using *** pip install aiml
import aiml
import os

# Debugging Purposes
from Gestures import Hand
from Gestures import Arm
from Gestures import Head

# Scripts
# from Scripts import scriptExample

#Gestures Class's
#TODO: Currently this broken
# hand = Hand()
# arm = Arm()
# head = Head()

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
    Hand_Max = hand.options.max()
    Arm_Max = arm.options.max()
    Head_Max = head.options.max()
    
    Hand_Current = 0
    Arm_Current = 0
    Head_Current = 0
    
    #Save info to varialbe
    User_Data = input("Your Input: ")
    
    if(User_Data == hand.options(0)):
      print("Hello World")
    
    else (Hand_Current > Hand_Max):
      Hand_Current++
    
    else (Hand_Current = Hand_Max):
      Hand_Current = 0
      
#Must be last thing to run
while True:
  message =  kurry.respond(raw_input("Kurry >> "))
  
  if message == "quit" or "Save":
    exit()
  else if message == "save" or "Save":
    kernel.saveBrain("Services/Voice/Chatbot/bot_brain.brn")
  else:
    bot_response = kurry.respond(message)