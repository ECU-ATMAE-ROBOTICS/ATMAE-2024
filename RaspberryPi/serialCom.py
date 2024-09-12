import serial
import struct
import pygame
import time

if __name__ == '__main__':
    arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    arduino.reset_input_buffer()
    arduino.reset_output_buffer()

    pygame.init()
    controller = pygame.joystick.Joystick(0)

    while True: 
        #Detects and sends controller inputs
        for event in pygame.event.get():
            if event.type == pygame.JOYBUTTONUP or  event.type == pygame.JOYBUTTONDOWN:
                value = int(controller.get_button(event.button))
                arduino.write(struct.pack("ii", event.button, value))

            if event.type == pygame.JOYAXISMOTION:
                axisValue = controller.get_axis(event.axis)
                arduino.write(struct.pack("if", event.axis + 15, axisValue))

            if event.type == pygame.JOYHATMOTION:
                value = 0
                
                # match controller.get_hat(event.hat) {
                #     case (0, 1): value = 0
                #     case (-1, 0): value = 1
                #     case (0, -1): value = 2
                #     case (1, 0): value = 3
                # }

                hatValue = controller.get_hat(event.hat)

                if hatValue == (0,0):
                    value = 0

                if hatValue == (0,1):
                    value = 1

                if hatValue == (-1,0):
                    value = 2

                if hatValue == (0,-1):
                    value = 3
                    
                if hatValue == (1,0):
                    value = 4 

                arduino.write(struct.pack("ii", 21, value))

