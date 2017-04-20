import time

class Arm():

  Bicep_Port = 8
  Rotate_Port = 9
  Shoulder_Port = 10
  Omoplate_Port = 11

  author = "Josh Brown"
  email = "Brownbear1002@gmail.com"
  version = "0.0.1"

  options = [
      "Connect Arm",
      "Attach Arm",
      "Disconnect Arm",
      "Detach Arm",
      "Rest",
      ####################################
      "Bicep 90",
      "Rotate 90",
      "Shoulder 90",
      "Omoplate 90",
      ####################################
      "Status"
    ]
    
  def Connect_Arm():
    print("Arm: Connecting")
    #TODO: Connect Arm ;)
    print("Arm: Connected")
    
    print("Arm: Resting Bicep")
    Rest_Bicep()
    time.sleep(2)
    print("Arm: Resting Rotate")
    Rest_Rotate()
    time.sleep(2)
    print("Arm: Resting Shoulder")
    Rest_Shoulder()
    time.sleep(2)
    print("Arm: Resting Omoplate")
    Rest_Omoplate()
    time.sleep(2)

  def Rest_All():
    print("Arm: Resting Bicep")
    Rest_Bicep()
    time.sleep(2)
    print("Arm: Resting Rotate")
    Rest_Rotate()
    time.sleep(2)
    print("Arm: Resting Shoulder")
    Rest_Shoulder()
    time.sleep(2)
    print("Arm: Resting Omoplate")
    Rest_Omoplate()
    time.sleep(2)
    
  def Status():
    print("Amr: Bicep Port [" + Bicep_Port + "] Rotate Port [" + Rotate_Port + "] Shoulder Port [" + Shoulder_Port + "] Omoplate [" + Omoplat_Port + "]" )
    
###################################

def Rest_Bicep():
  
def Rest_Rotate():
  
def Rest_Shoulder():
  
def Rest_Omoplate():
  
###################################

def Bicep_90():
  
def Rotate_90():
  
def Shoulder_90():
  
def Omoplate_90():

###################################

def Move_Custom_Left(Bicep, Rotate, Shoulder, Omoplate):

def Move_Custom_Right(Bicep, Rotate, Shoulder, Omoplate):
