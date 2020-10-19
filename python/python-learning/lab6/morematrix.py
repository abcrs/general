def order(m):
    count1=0
    for i in range(len(m)):
        count2=0
        for j in range(len(m[i])):
            count2+=1
        if count2!=len(m):
            return 0
        count1+=1
    return count1

def matrix(n, init):
    newmat=[]
    for i in range(0,n):
        newrow=[]
        for j in range(0,n):
            newrow.append(init)
        newmat.append(newrow)
    return newmat

def main():
    mat=matrix(6,5)
    #mat=[[3,2,1],[3,2],[3]]
    for i in range(len(mat)):
        print(mat[i])
    size=order(mat)
    print(size)

if __name__=='__main__':
    main()
