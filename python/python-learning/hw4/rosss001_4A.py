#CSCI 1133 Homework 4
#Anthony Ross-Sapienza
#Problem A

def two_sums(aList,target):
    for num in aList:
        if type(num)!=int:
            print("A non-integer number has been input. Fail!")
            exit()
    if type(target)!=int:
        print("A non-integer number has been input. Fail!")
        exit()
    for i in range(len(aList)):
        for j in range(i,len(aList)):
            if aList[i]+aList[j]==target:
                return((aList[i],aList[j]))
