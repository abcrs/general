#Anthony Ross-Sapienza
#CSCI 1133
#Problem 5D
import turtle

def drawSquare(t,leng):             #The only square that is drawn all at once is the smallest
    t.pd()
    t.fd(leng)
    t.right(90)
    t.fd(leng)
    t.right(90)
    t.fd(leng)
    t.right(90)
    t.fd(leng)
    t.right(90)
    t.pu()

def lineandReturn(t,leng):          #This is just to save space in the squares function
    t.fd(leng/2)
    t.left(180)
    t.pd()
    t.fd(leng)
    t.pu()
    t.left(180)
    t.fd(leng/2)

def squares(t,length,depth):
    t.pu()
    if depth==0:
        return
    elif depth==1:
        t.fd(length/2)
        t.left(90)
        t.fd(length/2)
        t.right(180)
        drawSquare(t,length)
        t.fd(length/2)
        t.right(90)
        t.fd(length)
        t.left(90)
    else:
        t.fd(length/2)
        t.right(90)
        lineandReturn(t,length)                 #The goal is to start each new call
        t.left(90)                              #At the same spot, the center of the square
        t.fd(length/4)                          #So the turtle moves into position to call the function
        squares(t,length/2,depth-1)             #And then moves back to the previous square to continue
        t.fd(length/2)
        t.right(90)
        t.fd(length/2)
        lineandReturn(t,length)
        t.left(90)
        t.fd(length/4)
        squares(t,length/2,depth-1)
        t.fd(length/2)
        t.right(90)
        t.fd(length/2)
        lineandReturn(t,length)
        t.left(90)
        t.fd(length/4)
        squares(t,length/2,depth-1)
        t.fd(length/2)
        t.right(90)
        t.fd(length/2)
        lineandReturn(t,length)
        t.left(90)
        t.fd(length/4)
        squares(t,length/2,depth-1)
        t.right(90)
        t.fd(length/2)
        t.right(90)
        t.fd(length/2)
        t.left(90)

def main():
    deep=int(input("How deep will you go? "))
    t=turtle.getturtle()
    t.speed(0)
    line=200
    squares(t,line,deep)

if __name__=='__main__':
    main()
