#Anthony Ross-Sapienza
#CSCI 1133
#Problem 5B
def baseConversion(num,base):
    quo=num//base
    rem=num%base
    if rem>9:                   #Remainder>10 means a capital letter is needed
        rem=chr(rem+55)         #chr finds capital letters in the range (65-90)
    else:                       #Combine the excess of the remainder, which is remainder-9, and add 64
        rem=str(rem)            #A remainder less than 9 means just using a digit is appropriate
    if quo==0:
        return rem              #A quotient of 0 is the base case
    else:
        return baseConversion(quo,base)+rem

def main():
    number=int(input("Enter your decimal number: "))
    nbase=int(input("Enter the base you want to convert to: "))
    nnum=baseConversion(number,nbase)
    print("{0} in base {1} is {2}".format(number,nbase,nnum))

if __name__=='__main__':
    main()
