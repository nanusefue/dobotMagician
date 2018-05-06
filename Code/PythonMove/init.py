import RPi.GPIO as GPIO
import time
import subprocess
from ScriptRobot import ScriptRobot
GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.IN, pull_up_down=GPIO.PUD_UP)

while True:
	input_state = GPIO.input(18)
	if input_state == True:
	    R = ScriptRobot()
	    R.Connect()
    	    R.ParserMove()
	    time.sleep(10)
