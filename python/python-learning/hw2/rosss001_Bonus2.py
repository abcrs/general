#CSCI 1133 Homework 2
#Anthony Ross-Sapienza
#Bonus Problem

import turtle

def drawSquare(times,length,inc):
    turtle.ht()
    angle=360/times
    rainbow=1
    while times>0:
        if times%2==0:
            if rainbow==1:
                turtle.color("red")
                turtle.begin_fill()
            elif rainbow==2:
                turtle.color("orange")
                turtle.begin_fill()
            elif rainbow==3:
                turtle.color("yellow")
                turtle.begin_fill()
            elif rainbow==4:
                turtle.color("green")
                turtle.begin_fill()
            elif rainbow==5:
                turtle.color("blue")
                turtle.begin_fill()
            elif rainbow==6:
                turtle.color("indigo")
                turtle.begin_fill()
            elif rainbow==7:
                turtle.color("violet")
                turtle.begin_fill()
            rainbow+=1
            if rainbow==8:
                rainbow=1
        for i in range(4):
            turtle.fd(length)
            turtle.left(90)
        length+=inc
        turtle.end_fill()
        turtle.color("black")
        turtle.left(angle)
        times-=1

def drawTriangle(times,length,inc):
    turtle.ht()
    angle=360/times
    rainbow=1
    while times>0:
        if times%2==0:
            if rainbow==1:
                turtle.color("red")
                turtle.begin_fill()
            elif rainbow==2:
                turtle.color("orange")
                turtle.begin_fill()
            elif rainbow==3:
                turtle.color("yellow")
                turtle.begin_fill()
            elif rainbow==4:
                turtle.color("green")
                turtle.begin_fill()
            elif rainbow==5:
                turtle.color("blue")
                turtle.begin_fill()
            elif rainbow==6:
                turtle.color("indigo")
                turtle.begin_fill()
            elif rainbow==7:
                turtle.color("violet")
                turtle.begin_fill()
            rainbow+=1
            if rainbow==8:
                rainbow=1
        for i in range(3):
            turtle.fd(length)
            turtle.left(120)
        length+=inc
        turtle.end_fill()
        turtle.color("black")
        turtle.left(angle)
        times-=1


def drawOctagon(times,length,inc):
    turtle.ht()
    angle=360/times
    rainbow=1
    while times>0:
        if times%2==0:
            if rainbow==1:
                turtle.color("red")
                turtle.begin_fill()
            elif rainbow==2:
                turtle.color("orange")
                turtle.begin_fill()
            elif rainbow==3:
                turtle.color("yellow")
                turtle.begin_fill()
            elif rainbow==4:
                turtle.color("green")
                turtle.begin_fill()
            elif rainbow==5:
                turtle.color("blue")
                turtle.begin_fill()
            elif rainbow==6:
                turtle.color("indigo")
                turtle.begin_fill()
            elif rainbow==7:
                turtle.color("violet")
                turtle.begin_fill()
            rainbow+=1
            if rainbow==8:
                rainbow=1
        for i in range(8):
            turtle.fd(length)
            turtle.left(45)
        length+=inc
        turtle.end_fill()
        turtle.color("black")
        turtle.left(angle)
        times-=1

def main():
    while True:
        shape=input("What kind of shape do you want to draw? ")
        if (shape.lower()=="square") or (shape.lower()=="triangle") or (shape.lower()=="octagon"):
            break
        else:
            print("ERROR: "+shape+" is not a valid choice. Plesae enter triangle, square, or octagon")
    many=int(input("How many would you like to draw? "))
    big=int(input("How big should the shapes be? "))
    increase=int(input("How much bigger should each shape get? "))
    if shape.lower()=="square":
        drawSquare(many,big,increase)
    elif shape.lower()=="triangle":
        drawTriangle(many,big,increase)
    elif shape.lower()=="octagon":
        drawOctagon(many,big,increase)

if __name__=='__main__':
    main()
