import serial
import pygame


if __name__ == '__main__':
    arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    arduino.reset_input_buffer()
    arduino.reset_output_buffer()

    message = ""

    pygame.init()
    controller = pygame.joystick.Joystick(0)

    #Checks for serial connection

    while arduino.in_waiting == 0:
        arduino.write("A\n".encode('utf-8'))

    print(arduino.readline().decode('utf-8').rstrip())

    while True:
       
        #Detects controller inputs
        for event in pygame.event.get():
            if event.type == pygame.JOYBUTTONUP or  event.type == pygame.JOYBUTTONDOWN:
                message = f"{event.button}:{controller.get_button(event.button)}\n"
                arduino.write(message.encode('utf-8'))

            if event.type == pygame.JOYAXISMOTION:
                axisValue = controller.get_axis(event.axis)
                message = f"{event.axis}:{round(axisValue,2)}\n"
                arduino.write(message.encode('utf-8'))

            if event.type == pygame.JOYHATMOTION:
               message = f"{event.hat}:{controller.get_hat(event.hat)}\n"
               arduino.write(message.encode('utf-8'))

        #Prints string in the buffer
        if arduino.in_waiting: 
            response = arduino.readline().decode('utf-8').rstrip()
            print(response)
