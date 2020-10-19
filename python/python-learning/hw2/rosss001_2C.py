#CSCI 1133 Homework 2
#Anthony Ross-Sapienza
#Problem C

import turtle

def drawSquare(times,length):
    turtle.ht()
    angle=360/times
    while times>0:
        for i in range(4):
            turtle.fd(length)
            turtle.left(90)
        turtle.left(angle)
        times-=1

def drawTriangle(times,length):
    turtle.ht()
    angle=360/times
    while times>0:
        for i in range(3):
            turtle.fd(length)
            turtle.left(120)
        turtle.left(angle)
        times-=1


def drawOctagon(times,length):
    turtle.ht()
    angle=360/times
    while times>0:
        for i in range(8):
            turtle.fd(length)
            turtle.left(45)
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
    if shape.lower()=="square":
        drawSquare(many,big)
    elif shape.lower()=="triangle":
        drawTriangle(many,big)
    elif shape.lower()=="octagon":
        drawOctagon(many,big)

if __name__=='__main__':
    main()
