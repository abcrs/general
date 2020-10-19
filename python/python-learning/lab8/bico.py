def choose(n,k):
    if k==0 or n==k:
        return 1
    else:
        return choose(n-1,k-1)+choose(n-1,k)

def main():
    top=int(input("Enter the 'n' value: "))
    bot=int(input("Enter the 'k' value: "))
    print(str(top)+" choose "+str(bot)+" is: ",end='')
    print(choose(top,bot))

if __name__=='__main__':
    main()
