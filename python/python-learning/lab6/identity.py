def identity(n):
    newmat=[]
    for i in range(0,n):
        newrow=[]
        for j in range(0,n):
            if j==i:
                newrow.append(1)
            else:
                newrow.append(0)
        newmat.append(newrow)
    return newmat

def main():
    newmatrix=identity(10)
    for i in range(len(newmatrix)):
        print(newmatrix[i])

if __name__=='__main__':
    main()
