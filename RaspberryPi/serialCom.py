#pip libs
import serial
import pygame
import sys
#built-in libs
import time
import asyncio

#internal files
from XboxController.XboxController import XboxController


pygame.init()
controller = pygame.joystick.Joystick(0)
DEAD_ZONE = .3



async def main():
    arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    arduino.reset_input_buffer()
    arduino.reset_output_buffer()
    
    message = None

    #Tests Serial Communication
    while arduino.in_waiting == 0:
        arduino.write("Testing\n".encode('utf-8'))
        time.sleep(1)

    print(arduino.readline().decode('utf-8').rstrip())

    while True:

        #Detects and sends controller inputs
        message = await controller.getControllerInput()

        if message != None:
            arduino.write(message.encode('utf-8'))

        #Prints string in the buffer
        if arduino.in_waiting: 
            response = arduino.readline().decode('utf-8').rstrip()
            print(response)
        
asyncio.run(main())
