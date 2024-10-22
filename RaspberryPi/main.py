# pip libs
import serial
import pygame
import sys
import serial.serialutil

# built-in libs
import time
import asyncio
import logging
import subprocess
import os

# internal files
from XboxController.XboxController import XboxController
from Util.util import *

script_dir = os.path.dirname(__file__)
subprocess.Popen([sys.executable, "camera/stream.py"], cwd=script_dir)

async def main():
    # Connect to the Arduino
    connected = False
    while not connected:
        try:
            arduino = serial.Serial("/dev/ttyACM0", 9600, timeout=1)
            arduino.reset_input_buffer()
            arduino.reset_output_buffer()
            connected = True
        except serial.serialutil.SerialException:
            logging.error("Couldn't connect to Arduino")
            time.sleep(1)

    connected = False

    # Connect to the Xbox Controller
    while not connected:
        try:
            pygame.init()
            controller = XboxController(deadZone=0.25)
            connected = True
        except pygame.error:
            logging.error("Couldn't connect to controller")
            pygame.joystick.quit()
        time.sleep(1)
    

    logging.info("Starting Testing")

    # Tests Serial Communication
    while arduino.in_waiting == 0:
        arduino.write("Testing\n".encode("utf-8"))
        time.sleep(1)

    print(arduino.readline().decode("utf-8").rstrip())
    logging.info("Ending Testing")
    
    prevInstruction = None
    while True:
        # Detects and sends controller inputs
        instructions = None
        instructions = await controller.getControllerInput()

        if instructions != None:
            for instruction in instructions:
                instructionID = int(instruction[:instruction.find(":")])
                instructionValue = float(instruction[instruction.find(":")+1:])
                
                if instructionID in validSticks or instructionID in validTriggers:
                    
                    if prevInstructions.get(instructionID) != instructionValue:
                        arduino.write(instruction.encode("utf-8"))

                    prevInstructions[instructionID] = instructionValue
                
                elif instructionID not in controller.inputIDs.get("A"):
                    arduino.write(instruction.encode("utf-8"))

        # Prints string in the buffer
        if arduino.in_waiting:
            response = arduino.readline().decode("utf-8").rstrip()
            print(response)

        await asyncio.sleep(0.02)


asyncio.run(main())
