#CSCI 1133 Homework 7
#Anthony Ross-Sapienza
#Problem A

class Complex():
    def __init__(self,ireal=0,iimag=0):
        self.real=ireal
        self.imag=iimag

    def __str__(self):
        if self.imag<=0:
            if self.imag<0:
                return str(self.real)+str(self.imag)+"i"
            else:
                return str(self.real)
        else:
            if self.real==0:
                return str(self.imag)+"i"
            else:
                return str(self.real)+"+"+str(self.imag)+"i"

    def __add__(self,rhand):
        return Complex(self.real+rhand.real,self.imag+rhand.imag)

    def __sub__(self,rhand):
        return Complex(self.real-rhand.real,self.imag-rhand.imag)

    def __mul__(self,rhand):
        return Complex(self.real*rhand.real-self.imag*rhand.imag,self.real*rhand.imag+self.imag*rhand.real)

    def __truediv__(self,rhand):
        if rhand.real==0 and rhand.imag==0:
            return None                         #None returned if the second complex number is 0 for both real and imaginary values
        divisor=rhand.real**2+rhand.imag**2     #For a less lengthy return line, the divisor is a variable because it's the same for both real and imaginary
        return Complex((self.real*rhand.real+self.imag*rhand.imag)/divisor,(self.imag*rhand.real-self.real*rhand.imag)/divisor)

def main():
    real1=float(input("Enter the real value of the first complex number: "))
    imag1=float(input("Enter the imaginary value of the first complex number: "))
    real2=float(input("Enter the real value of the second complex number: "))
    imag2=float(input("Enter the imaginary value of the second complext number: "))
    com1=Complex(real1,imag1)
    com2=Complex(real2,imag2)
    print("C1 =",com1)
    print("C2 =",com2)
    print("C1+C2 =",com1+com2)
    print("C1-C2 =",com1-com2)
    print("C1*C2 =",com1*com2)
    if com1/com2==None:
        print("C1/C2 = None; Divide by Zero Error!")
    else:
        print("C1/C2 =",com1/com2)


if __name__=='__main__':
    main()
