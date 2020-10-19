def roundit(jagnum):
    if jagnum>0:
        res=int(jagnum+.5)
    elif jagnum<0:
        res=int(jagnum-.5)
    elif jagnum==0:
        res=int(jagnum)
    return res
loop="y"
while loop=="y":
    num=float(input("Please enter a number: "))
    cir=roundit(num)
    print("The rounded number is: "+str(cir))
    loop=input("Would you like to keep rounding? y/n ")
