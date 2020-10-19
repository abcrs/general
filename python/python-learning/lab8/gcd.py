def gcd(a,b):
    rem=0
    if b==0:
        return a
    else:
        rem=a%b
        return gcd(b,rem)

def main():
    one=int(input("Enter the first number: "))
    two=int(input("Enter the second number: "))
    great=0
    if one<0:
        one=abs(one)
    if two<0:
        two=abs(two)
    if one<two:
        great=gcd(two,one)
    else:
        great=gcd(one,two)
    print("The greatest common divisor of "+str(one)+" and "+str(two)+" is "+str(great)+".")

if __name__=='__main__':
    main()
