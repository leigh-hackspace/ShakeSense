#!/usr/bin/env python3

import RPi.GPIO as GPIO
import time

red = 2
green = 3
blue = 4
motor = 17 #yellow LED

def setup():
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    GPIO.setup(red,GPIO.OUT)
    GPIO.setup(green,GPIO.OUT)
    GPIO.setup(blue,GPIO.OUT)
    GPIO.setup(motor,GPIO.OUT)
    
    GPIO.output(red, GPIO.LOW)
    GPIO.output(green, GPIO.LOW)
    GPIO.output(blue, GPIO.LOW)
    GPIO.output(motor, GPIO.LOW)

def blink(colour, length):
    GPIO.output(colour,GPIO.HIGH)
    time.sleep(length)
    GPIO.output(colour, GPIO.LOW)

setup()
blink(motor,2)
blink(red,1)
blink(motor,2)
blink(blue,2)
blink(motor,2)
blink(green,3)
blink(motor,2)
