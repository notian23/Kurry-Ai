import time
import Adafruit_BBIO as PMW

def Move_Custom_Left(Bicep, Rotate, Shoulder, Omoplate):
  print("Arm: Left Moving Bicep to" + Bicep)
  print("Arm: Left Moving Rotate to" + Rotate)
  print("Arm: Left Moving Shoulder to" + Shoulder)
  print("Arm: Left Moving Omoplate to" + Omoplate)

def Move_Custom_Right(Bicep, Rotate, Shoulder, Omoplate):
  print("Arm: Right Moving Bicep to" + Bicep)
  print("Arm: Right Moving Rotate to" + Rotate)
  print("Arm: Right Moving Shoulder to" + Shoulder)
  print("Arm: Right Moving Omoplate to" + Omoplate)

class Arm():

  Bicep_Port = 8
  Rotate_Port = 9
  Shoulder_Port = 10
  Omoplate_Port = 11

  Bicep_Min = 0
  Bicep_Max = 90

  Rotate_Min = 90
  Rotate_Max = 40

  Shoulder_Min = 30
  #Shoulder_Max = 

  Omoplate_Min = 10
  Omoplate_Max = 80

  author = "Josh Brown"
  email = "Brownbear1002@gmail.com"
  version = "0.0.1"

  options = {
      1 : "Connect Arm",
      2 : "Attach Arm",
      3 : "Disconnect Arm",
      4 : "Detach Arm",
      5 : "Rest",
      ####################################
      6 : "Bicep 90",
      7 : "Rotate 90",
      8 : "Shoulder 90",
      9 : "Omoplate 90",
      ####################################
      10 : "Bicep Custom",
      11 : "Rotate Custom",
      12 : "Shoulder Custom",
      13 : "Omoplate Custom",
      ####################################
      14 : "Status"
    }
    
  def Connect_Arm():
    print("Arm: Connecting")
    #TODO: Connect Arm ;)
    
    print("Arm: Connected")
    
    print("Arm: Resting Bicep")
    # Rest Part
    time.sleep(2)
    print("Arm: Resting Rotate")
    # Rest Part
    time.sleep(2)
    print("Arm: Resting Shoulder")
    # Rest Part
    time.sleep(2)
    print("Arm: Resting Omoplate")
    # Rest Part
    time.sleep(2)

  def Rest_All():
    print("Arm: Resting Bicep")
    # Rest Part
    time.sleep(2)
    print("Arm: Resting Rotate")
    # Rest Part
    time.sleep(2)
    print("Arm: Resting Shoulder")
    # Rest Part
    time.sleep(2)
    print("Arm: Resting Omoplate")
    # Rest Part
    time.sleep(2)
    
  def Status():
    print("Arm: Bicep Port [" + Bicep_Port + "] Rotate Port [" + Rotate_Port + "] Shoulder Port [" + Shoulder_Port + "] Omoplate [" + Omoplat_Port + "]" )
    
