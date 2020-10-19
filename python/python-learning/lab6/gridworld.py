import turtle
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
    mat=makematrix(50)
    populate(mat,500,1)
    screen=turtle.getscreen()
    screen.tracer(0)
    size=len(mat)-1
    screen.setworldcoordinates(0,0,size,size)
    turtle.color("red")
    turtle.up()
    turtle.hideturtle()
    for i in range(len(mat)):
        for j in range(len(mat[i])):
            if mat[i][j]!=0:
                turtle.goto(i,j)
                turtle.dot()
                screen.update()

if __name__=='__main__':
    main()
