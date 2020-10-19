import turtle
import random
def turnnmove():
    turn=(random.randint(1,4)-1)*90
    turtle.left(turn)
    turtle.fd(20)

def main():
    turtle.speed(0)
    turtle.setworldcoordinates(-200,-200,200,200)
    xLoc=abs(turtle.xcor())
    yLoc=abs(turtle.ycor())
    runs=0
    while (xLoc<200) and (yLoc<200):
        turnnmove()
        runs=runs+1
        xLoc=abs(turtle.xcor())
        yLoc=abs(turtle.ycor())
    turtle.pu()
    turtle.hideturtle()
    turtle.goto(0,0)
    turtle.pd()
    turtle.write(str(runs))

if __name__=='__main__':
    main()
