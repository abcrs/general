import random

def ssort(someList):
    low=0
    pos=0
    hold=0
    for i in range(len(someList)):
        low=someList[i]
        pos=i
        for j in range(i,len(someList)):
            if someList[j]<low:
                low=someList[j]
                pos=j
        hold=someList[i]
        someList[i]=low
        someList[pos]=hold

def main():
    n=int(input("Enter a number: "))
    sortList=[]
    for i in range(1,n+1):
        sortList.append(i)
    random.shuffle(sortList)
    print(sortList)
    ssort(sortList)
    print(sortList)

if __name__=='__main__':
    main()
