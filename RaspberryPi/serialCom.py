#pip libs
import serial
import pygame
import sys
#built-in libs
import time
import asyncio


pygame.init()
controller = pygame.joystick.Joystick(0)
DEAD_ZONE = .3

#Gets the values from the controller
async def getControllerInput():
    value = None
    for event in pygame.event.get():
        if event.type == pygame.JOYBUTTONUP or  event.type == pygame.JOYBUTTONDOWN:
            value = f"B:{event.button}:{controller.get_button(event.button)}\n"
            #arduino.write(message.encode('utf-8'))
            return value

        if event.type == pygame.JOYAXISMOTION:
            axisValue = controller.get_axis(event.axis)
        
            if axisValue > DEAD_ZONE or axisValue < DEAD_ZONE*-1 or event.axis == 4 or event.axis == 5:
                value = f"A:{event.axis}:{round(axisValue,2)}\n"

            else:
                value = f"A:{event.axis}:{0}\n"
            #arduino.write(message.encode('utf-8'))
            return value

        if event.type == pygame.JOYHATMOTION:
            value = f"D:{event.hat}:{controller.get_hat(event.hat)}\n"
            #arduino.write(message.encode('utf-8'))
            return value

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
        prevMessage = str(message)
        message = await getControllerInput()

        if message != None and message != prevMessage:
            arduino.write(message.encode('utf-8'))

        #Prints string in the buffer
        if arduino.in_waiting: 
            response = arduino.readline().decode('utf-8').rstrip()
            print(response)
        
asyncio.run(main())
