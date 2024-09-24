#pip libs
import serial

import pygame
import sys
#built-in libs
import time
import asyncio
import logging

import serial.serialutil

#internal files
from XboxController.XboxController import XboxController
    



async def main():
    
    #Connect to the Arduino
    connected = False
    while not connected:
        try:
            arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
            arduino.reset_input_buffer()
            arduino.reset_output_buffer()
            connected = True
        except serial.serialutil.SerialException:
            logging.error("Couldn't connect to Arduino")
            time.sleep(1)

    connected = False

    #Connect to the Xbox Controller
    while not connected:
        try:
            pygame.init()
            controller = XboxController(deadZone=.25)
            connected = True
        except pygame.error:
            logging.error("Couldn't connect to controller")
            pygame.joystick.quit()
        time.sleep(1)

    
    logging.info("Starting Testing")
    #Tests Serial Communication
    while arduino.in_waiting == 0:
        arduino.write("Testing\n".encode('utf-8'))
        time.sleep(1)

    print(arduino.readline().decode('utf-8').rstrip())
    logging.info("Ending Testing")
    while True:

        #Detects and sends controller inputs
        instructions = None
        instructions = await controller.getControllerInput()

        if instructions != None:
            for instruction in instructions:
                arduino.write(instruction.encode('utf-8'))

        #Prints string in the buffer
        if arduino.in_waiting: 
            response = arduino.readline().decode('utf-8').rstrip()
            print(response)
        
asyncio.run(main())
