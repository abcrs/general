import random

def makematrix(n):
    newmat=[]
    for i in range(0,n):
        newrow=[]
        for j in range(0,n):
            newrow.append(0)
        newmat.append(newrow)
    return newmat

def populate(m,n,value):
    k=0
    while k<n:
        row=random.randint(1,len(m))-1
        col=random.randint(1,len(m))-1
        if m[row][col]==0:
            m[row][col]=value
            k+=1


def main():
    mat=makematrix(5)
    populate(mat,10,5)
    for i in range(len(mat)):
        print(mat[i])

if __name__=='__main__':
    main()
