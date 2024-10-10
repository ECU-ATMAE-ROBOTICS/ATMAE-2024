#Axis that are registered as valid input
validSticks = [5]
validTriggers = [9, 10]

#Keeps track of previous inputs sent by an ID to prevent serial clogging
prevInstructions = {5:0.0, 9:0.0, 10:0.0}


#***May not be used in final version****
#Converts axis floating point value to a 0, 1, or -1
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