import serial
import pygame

class XboxController():
    pygame.init()
    _DEAD_ZONE= .3
    def __init__(self, controllerNum=0):

        self.controller = pygame.joystick.Joystick(controllerNum)

        self.numAxis = self.controller.get_numaxes()
        self.numButtons = self.controller.get_numbuttons()
        self.numDpadButtons = 5
        self.total = self.numAxis + self.numButtons + self.numDpadButtons

        self.inputIDs = {"D":[x for x in range(self.numDpadButtons)], "A":[x for x in range(self.numDpadButtons, self.total-self.numButtons)], "B":[x for x in range(self.total-self.numButtons , self.total)]}
    

    
    def getMappedButtons(self):
        print(self.inputIDs)



    #Gets the values from the controller
    async def getControllerInput(self):
        value = None
        for event in pygame.event.get():
            dictVal = self.inputIDs.get("B")
            if event.type == pygame.JOYBUTTONUP or  event.type == pygame.JOYBUTTONDOWN:
                value = f"{dictVal[event.button]}:{self.controller.get_button(event.button)}"
                return value

            if event.type == pygame.JOYAXISMOTION:
                axisValue = round(self.controller.get_axis(event.axis),2)
                dictVal = self.inputIDs.get("A")
            
                if axisValue > XboxController._DEAD_ZONE or axisValue < XboxController._DEAD_ZONE*-1 or event.axis == 4 or event.axis == 5:
                    value = f"{dictVal[event.axis]}:{axisValue}"
                else:
                    value = None
                
                return value

            if event.type == pygame.JOYHATMOTION:
                dictVal = self.inputIDs.get("D")
                dPadVal = self.controller.get_hat(event.hat)
                if dPadVal == (0,0):
                    value = f"{dictVal[0]}:{0}"
                elif dPadVal == (0,1):
                    value = f"{dictVal[1]}:{1}"
                if dPadVal == (1,0):
                    value = f"{dictVal[2]}:{2}"
                if dPadVal == (0,-1):
                    value = f"{dictVal[3]}:{3}"
                if dPadVal == (-1,0):
                    value = f"{dictVal[4]}:{4}"

                return value



            



            
