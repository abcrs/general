def emul(a,b):
    count=0
    mult=0
    product=0
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
    return product

def main():
    pro=emul(10,8)
    print(str(pro))

if __name__ == '__main__':
    main()
