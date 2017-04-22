#!/usr/bin/env python3
import aiml
import os

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

core = main()

core.init()

while running == True:
  message =  kury.respond(raw_input("User >> "))
  print("Kury >> " + kury.respond(message))
