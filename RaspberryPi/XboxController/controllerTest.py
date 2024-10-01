from XboxController import XboxController
import asyncio

controller = XboxController(deadZone=.25)

validSticks = [5]
validTriggers = [9, 10]



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
    
    prevInstruction = None

    while True:
        instructions = await controller.getControllerInput()
        
        if instructions != None:
            for instruction in instructions:
                instructionID = int(instruction[:instruction.find(":")])
                
                if instructionID in validSticks or instructionID in validTriggers:
                    instruction = getDigitalAxis(instruction)
                    
                    if prevInstruction != instruction:
                        print(instruction)

                    prevInstruction = instruction
                
                elif instructionID not in controller.inputIDs.get("A"):
                    print(instruction)
                
                    
    
asyncio.run(main())
