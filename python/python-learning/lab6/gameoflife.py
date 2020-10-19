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
        row=random.randint(50,len(m))-25
        col=random.randint(50,len(m))-25
        if m[row][col]==0:
            m[row][col]=value
            k+=1

def makegrid(scr,ma):
    for i in range(len(ma)):
        for j in range(len(ma[i])):
            if ma[i][j]!=0:
                turtle.goto(i,j)
                turtle.dot()
                scr.update()

def neighbors(mat,x,y):
    life=0
    xd=x-1
    xu=x+1
    yd=y-1
    yu=y+1
    for i in range(xd,xu):
        for j in range(yd,yu):
            if i<0 or i==len(mat):
                life+=0
            elif j<0 or j==len(mat):
                life+=0
            if mat[i][j]==1:
                life+=1
    if mat[x][y]==1:
        if life>3:
            return 0
        elif life>=2:
            return 1
        elif life<2:
            return 0
    if mat[x][y]==0:
        if life==3:
            print("It happened")
            return 1
        else:
            return 0

def copy(mat1):
    newmat=[]
    for i in range(len(mat1)):
        newc=[]
        for j in range(len(mat1[i])):
            newc.append(mat1[i][j])
        newmat.append(newc)
    return newmat



def main():
    live=0
    gen=0
    current=makematrix(100)
    new=[]
    populate(current,1500,1)
    screen=turtle.getscreen()
    size=len(current)-1
    screen.setworldcoordinates(0,0,size,size)
    screen.tracer(10)
    turtle.color("red")
    turtle.up()
    turtle.hideturtle()
    makegrid(screen,current)
    while gen<50:
        new=copy(current)
        for i in range(0,len(current)):
            for j in range(0,len(current)):
                live=neighbors(current,i,j)
                if live==1:
                    new[i][j]=1
                else:
                    new[i][j]=0
        turtle.textinput("","Go?")
        turtle.clear()
        makegrid(screen,new)
        current=copy(new)
        gen+=1

if __name__=='__main__':
    main()
