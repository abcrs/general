import turtle
import random
import math
def dartLand(x,y):
    z=math.sqrt(x*x+y*y)
    if z>150:
        res="red"
    else:
        res="green"
    return res
def dartThrow(numIn):
    xLoc=random.uniform(-1,1)*150
    yLoc=random.uniform(-1,1)*150
    turtle.goto(xLoc,yLoc)
    color=dartLand(xLoc,yLoc)
    turtle.dot(5,color)
    if color == "green":
        numIn=numIn+1
    return numIn

def imageDraw():
    turtle.pu()
    turtle.right(90)
    turtle.fd(150)
    turtle.pd()
    turtle.left(90)
    turtle.circle(150)
    turtle.fd(150)
    turtle.left(90)
    turtle.fd(300)
    turtle.left(90)
    turtle.fd(300)
    turtle.left(90)
    turtle.fd(300)
    turtle.left(90)
    turtle.fd(150)
def main():
    turtle.speed(0)
    imageDraw()
    iteration=1000
    inside=0
    turtle.pu()
    turtle.hideturtle()
    while iteration>0:
        inside=dartThrow(inside)
        iteration=iteration-1
    turtle.goto(0,-175)
    area=inside/1000
    turtle.write(str(area),font=("Arial",15,"normal"))

if __name__=="__main__":
    main()
