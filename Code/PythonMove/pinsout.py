#https://sourceforge.net/p/raspberry-gpio-python/wiki/Inputs/
#use interruptions for call any funcion in python Scrypt
import RPi.GPIO as GPIO
import time

class io: 

    def __init__(self):
        self.pint
        self.modePin
        self.channel = GPIO.wait_for_edge(self.channel, GPIO_RISING, timeout=5000)
        GPIO.add_event_detect(self.channel, GPIO.RISING)  # add rising edge detection on a channel
        GPIO.add_event_detect(self.channel, GPIO.RISING, callback=action)  # add rising edge detection on a channel


    def action(channel):
        print('This is a edge event callback function!')
        print('Edge detected on channel %s'%self.channel)
        print('This is run in a different thread to your main program')

    def detach():
        GPIO.remove_event_detect(self.channel)

if __name__ == "__main__":
    R = io()
