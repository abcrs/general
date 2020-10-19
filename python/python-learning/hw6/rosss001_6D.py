#CSCI 1133 Homework 6
#Anthony Ross-Sapienza
#Problem D
import turtle

class Caterpillar():
    def __init__(self,bodycolor="green",legcolor="purple",bodysize=50):
        self.bodyc=bodycolor
        self.legc=legcolor
        self.bodys=bodysize
        self.t=turtle.getturtle()
        self.t.hideturtle()
        self.t.speed(0)
        self.display()

    def display(self):
        self.draw_antennae()
        self.draw_legs()
        self.draw_body()

    def draw_body(self):
        self.t.pu()
        self.t.goto(0,0)
        self.t.seth(0)
        self.t.fillcolor(self.bodyc)
        for i in range(5):
            self.t.begin_fill()
            self.t.circle(self.bodys)
            self.t.end_fill()
            self.t.left(90)
            self.t.fd(self.bodys)
            self.t.right(90)

    def draw_antennae(self):
        self.t.pu()
        self.t.goto(0,self.bodys*5)
        self.t.color(self.legc)
        self.t.left(120)
        self.t.pd()
        self.t.fd(self.bodys*2)
        self.t.pu()
        self.t.right(180)
        self.t.fd(self.bodys*2)
        self.t.left(120)
        self.t.pd()
        self.t.fd(self.bodys*2)
        self.t.pu()


    def draw_legs(self):
        self.t.pu()
        self.t.color(self.legc)
        y=1
        while y<=4:
            self.t.goto(0,self.bodys*y)
            self.t.seth(0)
            self.t.pd()
            self.t.fd(self.bodys*2)
            self.t.right(30)
            self.t.fd(self.bodys)
            self.t.pu()
            self.t.goto(0,self.bodys*y)
            self.t.seth(180)
            self.t.pd()
            self.t.fd(self.bodys*2)
            self.t.left(30)
            self.t.fd(self.bodys)
            self.t.pu()
            y+=1

class Butterfly(Caterpillar):
    def __init__(self,bodycolor="green",legcolor="purple",wingcolor="red",bodysize=50):
        self.wingc=wingcolor
        Caterpillar.__init__(self,bodycolor,legcolor,bodysize)

    def display(self):
        self.t.speed(0)
        Caterpillar.display(self)
        self.draw_wings()

    def draw_wings(self):
        self.t.pu()
        self.t.goto(-self.bodys*2.5,-self.bodys/2)
        self.t.seth(90)
        self.t.fillcolor(self.wingc)
        self.t.begin_fill()
        self.t.fd(self.bodys*6)
        self.t.right(120)
        self.t.fd(self.bodys*2.88675134595)             #2.88675134595 is about the length the hypotenuse of a 30/60/90 triangle where the longer side is 2.5
        self.t.left(60)                                 #Which gets the turtle back to the midpoint of the Caterpillar's body
        self.t.fd(self.bodys*2.88675134595)
        self.t.seth(270)
        self.t.fd(self.bodys*6)
        self.t.right(120)
        self.t.fd(self.bodys*2.88675134595)
        self.t.left(60)
        self.t.fd(self.bodys*2.88675134595)
        self.t.end_fill()
