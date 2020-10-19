def fibonacci(n):
    if n<=1:
        return n
    else:
        return fibonacci(n-1)+fibonacci(n-2)

def fiboPrint(ind):
    for i in range(0,ind+1):
        print(fibonacci(i),end=" ")
    print("")

def main():
    fiboPrint(20)

if __name__=='__main__':
    main()
