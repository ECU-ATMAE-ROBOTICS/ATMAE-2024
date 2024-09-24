import serial
import pygame

class XboxController():

    def __init__(self, controllerNum : int = 0, deadZone : float = 0):
        pygame.init()
        
        self.controller = pygame.joystick.Joystick(controllerNum)
        self.deadZone = deadZone

        self.controllerName = self.controller.get_name()
        self.numAxis = self.controller.get_numaxes()
        self.numButtons = self.controller.get_numbuttons()
        self.numDpadButtons = 5
        self.total = self.numAxis + self.numButtons + self.numDpadButtons

        self.inputIDs = {"D":[id for id in range(self.numDpadButtons)], 
                         "A":[id for id in range(self.numDpadButtons, self.total-self.numButtons)], 
                         "B":[id for id in range(self.total-self.numButtons , self.total)]}
    
    def getDetectedButtons(self):
        for buttonType in self.inputIDs.keys():
            print(f"{buttonType}: {self.inputIDs.get(buttonType)}")
    
    def getRawButton(self, buttonID : int) -> int:
        return self.controller.get_button(buttonID)
    
    def getRawAxis(self, axisID : int) -> float:
        return self.controller.get_axis(axisID)
    
    def getRawdPad(self, dPadID : int) -> tuple[int,int]:
        return self.controller.get_hat(dPadID)


    #Gets the values from the controller
    async def getControllerInput(self):
        message = []
        for event in pygame.event.get():
            if event.type == pygame.JOYBUTTONUP or  event.type == pygame.JOYBUTTONDOWN:
                dictVal = self.inputIDs.get("B")
                value = f"{dictVal[event.button]}:{self.controller.get_button(event.button)}\n"
                message.append(value)

            if event.type == pygame.JOYAXISMOTION:
                axisValue = round(self.controller.get_axis(event.axis),2)
                dictVal = self.inputIDs.get("A")
            
                if axisValue > self.deadZone or axisValue < self.deadZone*-1 or event.axis == 4 or event.axis == 5:
                    value = f"{dictVal[event.axis]}:{axisValue}\n"
                    message.append(value)
                else:
                    value = f"{dictVal[event.axis]}:0\n"
                    message.append(value)
                    

                            

            if event.type == pygame.JOYHATMOTION:
                dictVal = self.inputIDs.get("D")
                dPadVal = self.controller.get_hat(event.hat)
                if dPadVal == (0,0):
                    value = f"{dictVal[0]}:{0}\n"
                    message.append(value)
                elif dPadVal == (0,1):
                    value = f"{dictVal[1]}:{1}\n"
                    message.append(value)

                elif dPadVal == (1,0):
                    value = f"{dictVal[2]}:{2}\n"
                    message.append(value)

                elif dPadVal == (0,-1):
                    value = f"{dictVal[3]}:{3}\n"
                    message.append(value)

                elif dPadVal == (-1,0):
                    value = f"{dictVal[4]}:{4}\n"
                    message.append(value)

        return message



            



            
