#CSCI 1133 Homework 6
#Anthony Ross-Sapienza
#Problem C
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
        self.draw_antennae()                        #To avoid the legs and antennae showing up over the body
        self.draw_legs()                            #Those functions are called first
        self.draw_body()

    def draw_body(self):
        self.t.pu()
        self.t.goto(0,0)
        self.t.seth(0)                              #The heading is reset to make sure the circles are drawn correctly
        self.t.fillcolor(self.bodyc)
        for i in range(5):                          #This is repeated to avoid lengthier code
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
        while y<=4:                             #This is repeated to avoid lengthier code
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
