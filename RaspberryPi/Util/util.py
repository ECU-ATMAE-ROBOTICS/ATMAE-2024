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