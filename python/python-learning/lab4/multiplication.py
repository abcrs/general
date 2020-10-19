def mul(a,b):
    start=0
    count=0
    product=0
    if a>b:
        count=b
        mult=a
    else:
        count=a
        mult=b
    while (start<count):
        start+=1
        product+=mult
    return mult

def main():
    pro=mul(42,9)
    print(str(pro))

if __name__ == '__main__':
    main()
