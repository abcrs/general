def emul(a,b):
    count=0
    mult=0
    product=0
    neg=1
    if (a<0):
        neg=-1
        a*=-1
        if (b<0):
            b*=-1
            neg=1
    elif (b<0):
        neg=-1
        b*=-1
    if a>b:
        count=b
        mult=a
    else:
        count=a
        mult=b
    while (count>0):
        if (count%2)>0:
            product+=mult
        count//=2
        mult*=2
    product*=neg
    return product

def main():
    pro=emul(10,-9)
    print(str(pro))

if __name__ == '__main__':
    main()
