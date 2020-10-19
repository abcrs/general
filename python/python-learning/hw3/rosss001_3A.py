#CSCI 1133 Homework 3
#Anthony Ross-Sapienza
#Problem A

def intvert(lst):
    newList=[]
    count=len(lst)-1
    while count>=0:
        if type(lst[count])==int:
            newList.append(lst[count])
        count-=1
    return newList
