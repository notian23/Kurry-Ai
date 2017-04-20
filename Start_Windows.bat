@echo off
echo
echo Starting Kurry AI
echo
echo Killing current Java threads
taskkill.exe /F /IM java.exe
taskkill.exe /F /IM javaW.exe
echo
echo Cleaning free space on disk
echo
del myrobot.log
echo .
echo
move /y %cd%\myrobotlab-*.jar %cd%\myrobotlab.jar
if not exist %cd%\repo.json (
RMDIR /S /Q .myrobotlab
RMDIR /S /Q haarcascades
RMDIR /S /Q hogcascades
RMDIR /S /Q lbpcascades
RMDIR /S /Q libraries
RMDIR /S /Q pythonModules
RMDIR /S /Q repo
RMDIR /S /Q resource
RMDIR /S /Q tessdata
del ivychain.xml
del myrobotlab.log
del repo.json
)
echo
echo Installing Dependecies with mrl service because it is needed to run. This may take a long time
echo
timeout 2 > NUL
java -jar myrobotlab.jar -install
echo
echo Installation Complete
echo
cls
if not exist %cd%\InmoovScript\Inmoov.py (
    echo ERROR : %cd%\InmoovScript\Inmoov.py DOES NOT EXIST
    echo PLEASE PUT SCRIPT AND FOLDERS INSIDE InmoovScript FOLDER
    timeout 10 > NUL
) else (
java -jar myrobotlab.jar -invoke python execFile %cd%/InmoovScript/Inmoov.py -service python Python
)