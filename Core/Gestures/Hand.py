def Thumb_Open():
  print("Hand: Opening Thumb")

def Index_Open():
  print("Hand: Opening Index")
  
def Majeure_Open():
  print("Hand: Opening Majeure")
  
def Ring_Open():
  print("Hand: Opening Ring")
  
def Pinky_Open():
  print("Hand: Opening Pinky")

def Thumb_Closed():
  print("Hand: Closing Thumb")
  
def Index_Closed():
  print("Hand: Closing Index")
  
def Majeure_Closed():
  print("Hand: Closing Majeure")
  
def Ring_Closed():
  print("Hand: Closing Ring")
  
def Pinky_Closed():
  print("Hand: Closing Pinky")
  
def Move_Custom_Left(Thumb, Index, Majeure, Ring, Pinky):
  print("Hand: Moving left thumb to position [" + Thumb + "]")
  print("Hand: Moving left index to position [" + Index + "]")
  print("Hand: Moving left majeure to position [" + Majeure + "]")
  print("Hand: Moving left ring to position [" + pinky + "]")

def Move_Custom_Right(Thumb, Index, Majeure, Ring, Pinky):
  print("Hand: Moving right thumb to position [" + Thumb + "]")
  print("Hand: Moving right index to position [" + Index + "]")
  print("Hand: Moving right majeure to position [" + Majeure + "]")
  print("Hand: Moving right ring to position [" + pinky + "]")

class Hands():

  Thumb_Port = 2
  Index_Port = 3
  Majeure_Port = 4
  Ring_Port = 5
  Pinky_Port = 6

  Wrist_Port = 7
  

  author = "Josh Brown"
  email = "Brownbear1002@gmail.com"
  version = "0.0.1"


  options = [
      "Attach Hands",
      "Connect Hands",
      "Detach Hands",
      "Disconnect Hands",
      "Open Both Hands",
      "Open your hands",
      "Close Both Hands",
      "Close you hands",
      "Close your left hand",
      "Close your right hand",
      #####################################
      "Close your Left Thumb finger"
      "Close your Left Index finger",
      "Close your Left Majeure Finger",
      "Close your Left Ring Finger",
      "Close your Left Pinky Finger"
      "Open your Left Thumb finger"
      "Open your Left Index finger",
      "Open your Left Majeure Finger",
      "Open your Left Ring Finger",
      "Open your Left Pinky Finger",
      #####################################
      "Status"
    ]
  
  def Connect_Hand():
    print("Hand: Connecting")
    
    print("Hand: Connected")
    print("Hand: Opening Both Hands")
    Both_Open()
    
  def Disconnect_Hand():
    print("Hand: Disconecting")
    print("Hand: Opening Both Hands")
    Both_Open()
    
  def Open_Both_Hands():
    print("Hand: Opening")
    Both_open()
  
  def Closed_Both_Hands():
    print("Hand: Closing")
    Both_Closed()
  
  def Closed_Left_Hand():
    print("Hand: Closing left hand")
    Left_Closee()
    
  def Closed_Right_Hand():
    print("Hand: Closing right hand")
    Right_Closed()
    
  def Status():
    print("Status [dataString1, dataString2, dataString3]")