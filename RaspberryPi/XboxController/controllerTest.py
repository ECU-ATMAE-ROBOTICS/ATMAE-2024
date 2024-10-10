from XboxController import XboxController
import asyncio

#Python file for testing changes in controller code prior to being put in main


controller = XboxController(deadZone=.25)

validSticks = [5]
validTriggers = [9, 10]
prevInstructions = {5:0.0, 9:0.0, 10:0.0}


def getDigitalAxis(instruction):
    ID = int(instruction[:instruction.find(":")])
    value = float(instruction[instruction.find(":")+1:-1])

    if ID in validSticks:
        if value > 0:
            return f"{ID}:1\n"
        elif value < 0:
            return f"{ID}:-1\n"
        else:
            return f"{ID}:0\n"
        
    elif ID in validTriggers:
        if value > -.35:
            return f"{ID}:1\n"
        else:
            return f"{ID}:0\n"
    




async def main():

    controller.getLayout()

    while True:
        instructions = await controller.getControllerInput()
        
        if instructions != None:
            for instruction in instructions:
                instructionID = int(instruction[:instruction.find(":")])
                instructionValue = float(instruction[instruction.find(":")+1:])
                
                if instructionID in validSticks or instructionID in validTriggers:

                    if prevInstructions.get(instructionID) != instructionValue:
                        print(instruction, end='')

                    prevInstructions[instructionID] = instructionValue
                
                elif instructionID not in controller.inputIDs.get("A"):
                    print(instruction, end='')
                
                    
    
asyncio.run(main())
