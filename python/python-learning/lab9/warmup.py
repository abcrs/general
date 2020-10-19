def makeDictionary(list1,list2):
    scoreDict={}
    for i in range(len(list1)):
        scoreDict[list1[i]]=list2[i]
        print(list1[i])
    return scoreDict

def getScore(name,data):
    if name in data:
        return data[name]
    else:
        print("This is not a valid entry!")
        return -1
