@echo off
echo
echo
echo Killing all Java proccesses
echo
taskkill /im javaw.ex
echo Starting Program
echo 
cd Core && python main.py
