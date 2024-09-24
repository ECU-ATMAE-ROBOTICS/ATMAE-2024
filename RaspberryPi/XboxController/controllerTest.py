from XboxController import XboxController
import asyncio

controller = XboxController(deadZone=.25)

async def main():

    controller.getDetectedButtons()

    while True:
        instructions = await controller.getControllerInput()
        if instructions != None:
            for instruction in instructions:
                print(instruction)
    
asyncio.run(main())