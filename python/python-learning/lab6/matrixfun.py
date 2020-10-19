def matrix(n, init):
    newmat=[]
    for i in range(0,n):
        newrow=[]
        for j in range(0,n):
            newrow.append(init)
        newmat.append(newrow)
    return newmat

def main():
    value=int(input("Enter the initial value: "))
    order=int(input("Enter the order of the matrix: "))
    newmatrix=matrix(order,value)
    for i in range(len(newmatrix)):
        print(newmatrix[i])

if __name__=='__main__':
    main()
