#!/usr/bin/env python3
# Remember to install aiml using *** pip install aiml
import aiml
import os

# Aiml
kury = aiml.Kernel()
sessionId = 00001

# Loading Files
kury.learn("Services/Voice/Chatbot/bot.aiml")

running = True

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
    

while running == True:
  message =  kury.respond(raw_input("User >> "))
  print("Chatbot >> " + kury.respond(message))
