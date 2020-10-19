import turtle

def fillBox(color,x,y):
    turtle.color(color)
    turtle.begin_fill()
    turtle.fd(y)
    turtle.right(90)
    turtle.fd(x)
    turtle.right(90)
    turtle.fd(y)
    turtle.right(90)
    turtle.fd(x)
    turtle.right(90)
    turtle.end_fill()

def main():
    scr=turtle.Screen()
    scr.setworldcoordinates(-80,-80,80,80)
    turtle.ht()
    turtle.penup()
    turtle.speed(0)
    turtle.goto(-80,80)
    across=8
    down=8
    count=0
    col="red"
    while(down>0):
        while(across>0):
            if count%2==0:
                col="red"
            else:
                col="black"
            fillBox(col,20,20)
            turtle.fd(20)
            count+=1
            across-=1
        count+=1
        yco=turtle.ycor()-20
        turtle.goto(-80,yco)
        across=8
        down-=1



if __name__=='__main__':
    main()
