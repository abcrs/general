#Anthony Ross-Sapienza
#CSCI 1133
#Problem 5C
def facto(num):
    if num==1:
        return 1
    else:
        return num*facto(num-1)

def taylorSeries(ang,term):
    if term==1:
        return ang
    else:
        if term%2==0:       #Checks the term. An even term is subtracted, an odd term is added
            return -(ang**(term*2-1))/(facto(term*2-1))+taylorSeries(ang,term-1)
        else:               #Term is multiplied by 2 and 1 is subtracted to find the appropriate odd number
            return (ang**(term*2-1))/(facto(term*2-1))+taylorSeries(ang,term-1)

def main():
    angle=float(input("Enter the angle to approximate (in radians): "))
    terms=int(input("Enter the number of terms to compute: "))
    sin=taylorSeries(angle,terms)
    print("sin({0}) is approximately {1}".format(angle,sin))

if __name__=='__main__':
    main()
