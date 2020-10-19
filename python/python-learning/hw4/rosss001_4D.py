#CSCI 1133 Homework 4
#Anthony Ross-Sapienza
#Problem C

import rosss001_4A

def main():
    go='y'
    while go.lower()=='y':
        targetCheck=1
        listCheck=1
        target=input("Input target: ")
        while targetCheck==1:
            bad=False                           #bad remains false if integer is entered
            for a in target:                    #The whole string is checked, to not assume only single digits or positive numbers
                if a not in "-0123456789":
                    bad=True                    #bad changes to true if a non-integer is entered
            if bad:                             #Which then prompts the program to re-enter a valid integer
                target=input("Target must be an integer. Enter a valid target: ")
            else:
                target=int(target)              #If target is an integer, the string is converted to int
                targetCheck=0
        numString=input("Input list of numbers separate by a space: ")
        while listCheck==1:
            numList=numString.split(' ')
            bad=False                           #bad does the same for the list, but has to check each element
            for i in range(len(numList)):
                for b in numList[i]:
                    if b not in "-0123456789":
                        bad=True
            if bad:
                numString=input("The list can only contain integers. Enter a valid list: ")
            else:
                for j in range(len(numList)):   #And each element has to be converted to int
                    numList[j]=int(numList[j])  #This way the program works for positive and negative integers
                listCheck=0
        numSum=rosss001_4A.two_sums(numList,target)
        print("The two numbers that sum up to {0} are {1} and {2}.\n".format(target,numSum[0],numSum[1]))
        go=input("Would you like to enter another list and target? (y/n): ")

if __name__=='__main__':
    main()
