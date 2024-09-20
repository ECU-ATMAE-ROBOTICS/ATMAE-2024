from XboxController import XboxController
import asyncio

controller = XboxController()

async def main():

    controller.getMappedButtons()

    while True:
        value = await controller.getControllerInput()
        if value != None:
            print(value)
    
asyncio.run(main())