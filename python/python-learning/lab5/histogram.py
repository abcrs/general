import random

def diceRoll():
    d1=random.randint(1,6)
    d2=random.randint(1,6)
    newroll=d1+d2
    return newroll

def main():
    rollCount=[0]*11
    count=10000
    new=0
    while count>0:
        new=diceRoll()
        rollCount[new-2]+=1
        count-=1
    for i in range(len(rollCount)):
        num=i+2
        print(str(num)+": "+str(rollCount[i]))

if __name__=='__main__':
    main()
