import turtle
import random

def prepTime(t,y,color):
    t.pu()
    t.shape("turtle")
    t.color(color)
    t.goto(0,y)

def raceForward(t):
    move=random.randint(1,15)
    t.fd(move)
    return t.xcor()

def main():
    turtle.setworldcoordinates(0,0,150,70)
    nikki=turtle.Turtle()
    nikx=0
    prepTime(nikki,50,"green")
    henry=turtle.Turtle()
    henx=0
    prepTime(henry,35,"red")
    jordan=turtle.Turtle()
    jorx=0
    prepTime(jordan,20,"blue")
    while True:
        nikx=raceForward(nikki)
        henx=raceForward(henry)
        jorx=raceForward(jordan)
        if (nikx>=150):
            break
        if (henx>=150):
            break
        if (jorx>=150):
            break


if __name__=='__main__':
    main()
