import turtle
import random
import shape
from shape import Shape
from shape import Circle
from shape import Rectangle
from shape import Triangle
from shape import Square

class Display():
    def __init__(self):
        self.myt=turtle.getturtle()
        self.myt.speed(0)
        self.myt.hideturtle()
        self.elements=[]
        self.palatte=["red","pink","magenta","green","lime green","dark green","blue","sky blue","azure","yellow","olive","gold","purple","medium violet red","orange","chocolate","brown","sandy brown","peru","black","white","white smoke","slate gray","dark gray"]
        self.scr=self.myt.getscreen()
        self.scr.delay(0)
        self.scr.onclick(self.mouseEvent)
        self.scr.listen()

    def mouseEvent(self,x,y):
        random.shuffle(self.palatte)
        tall=random.randint(10,100)
        wide=random.randint(10,100)
        coin=random.randint(1,4)
        if coin==1:
            shape=Circle(x,y,tall)
        elif coin==2:
            shape=Rectangle(x,y,wide,tall)
        elif coin==3:
            shape=Triangle(x,y,tall)
        elif coin==4:
            shape=Square(x,y,tall)
        shape.setFilled(True)
        shape.setFillcolor(self.palatte[0])
        check=False
        for s in self.elements:
            if s.isIN(x,y):
                self.remove(s)
                check=True
        if check==False:
            shape.draw(self.myt)
            self.add(shape)

    def add(self,shape):
        self.elements.append(shape)
        shape.draw(self.myt)

    def remove(self,shape):
        self.elements.remove(shape)
        self.myt.clear()
        for s in self.elements:
            s.draw(self.myt)
