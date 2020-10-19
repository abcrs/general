#CSCI 1133 Homework 3
#Anthony Ross-Sapienza
#Problem C

def summation(low,up,func):
    total=0
    while low<=up:
        if func=="square":
            total=total+(low*low)
        if func=="cube":
            total=total+(low*low*low)
        if func=="inverse":
            total=total+(1/low)
        low+=1
    return total

def main():
    lower=int(input("Enter a lower bound for summation: "))
    upper=int(input("Enter an uppder bound for summation: "))
    fun=input("Enter a function to be summed (square, cube, inverse): ").lower()
    if lower<=0 and 0<=upper and fun=="inverse":
        print("Error. Can not divide by 0.")
    else:
        result=summation(lower,upper,fun)
        print("The result of the summation is "+str(result))


if __name__=='__main__':
    main()
