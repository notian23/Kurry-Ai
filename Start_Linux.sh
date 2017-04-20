@echo off
echo
echo Starting Kurry AI
echo
echo Killing current Java threads
# This command should kill any and all java commands... that run in a jar, hopefully
pkill -f 'java -jar'
echo
echo Cleaning Logs
echo
rm myrobotlab.log
echo .
echo
echo Updating MRL Installation
echo
#TODO: Edit version later
cp myrobotlab-XXXX.jar myrobotlab.jar

#TODO: Complete file
