#CSCI 1133 Homework 2
#Anthony Ross-Sapienza
#Problem A

def newFib(one, two, term):
    count=2
    current=two
    last=one
    new=0
    output=str(one)+" "+str(two)
    while (count<term):
        new=current+last
        last=current
        current=new
        output=output+" "+str(new)
        count+=1
    print('\n'+"The first "+str(term)+" terms of the new series are:"+'\n')
    print(output)

def main():
    first=int(input("Enter the first term of the series: "))
    second=int(input("Enter the second term of the series: "))
    terms=int(input("Enter the number of terms you want to see: "))
    newFib(first, second, terms)

if __name__=='__main__':
    main()
