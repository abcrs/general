class Shape():
    def __init__(self,ix=0,iy=0,icolor="Null",ifill=False):
        self.x=ix
        self.y=iy
        self.color=icolor
        self.fill=ifill

    def setFillcolor(self,cchange):
        self.color=cchange

    def setFilled(self,cfill):
        self.fill=cfill

    def isFilled(self):
        return self.fill

class Circle(Shape):
    def __init__(self,ix=0,iy=0,irad=1):
        Shape.__init__(self,ix,iy)
        self.rad=irad

    def draw(self,turt):
        turt.pu()
        turt.goto(self.x,self.y)
        turt.pd()
        if self.fill==True:
            turt.fillcolor(self.color)
            turt.begin_fill()
            turt.circle(self.rad)
            turt.end_fill()
        else:
            turt.circle(self.rad)

    def isIN(self,nx,ny):
        cent=self.y+self.rad
        d=((nx-self.x)**2+(ny-cent)**2)**.5
        if d>self.rad:
            return False
        return True


class Rectangle(Shape):
    def __init__(self,ix=0,iy=0,iwide=1,ihigh=1):
        Shape.__init__(self,ix,iy)
        self.wide=iwide
        self.high=ihigh

    def draw(self,turt):
        turt.pu()
        turt.goto(self.x,self.y)
        turt.pd()
        if self.fill==True:
            turt.fillcolor(self.color)
            turt.begin_fill()
            for i in range(2):
                turt.fd(self.wide)
                turt.right(90)
                turt.fd(self.high)
                turt.right(90)
            turt.end_fill()
        else:
            for i in range(2):
                turt.fd(self.wide)
                turt.right(90)
                turt.fd(self.high)
                turt.right(90)

    def isIN(self,nx,ny):
        if nx<=(self.x+self.wide) and nx>=self.x:
            if ny>=(self.y-self.high) and ny<=(self.y):
                return True
        return False

class Triangle(Shape):
    def __init__(self,ix=0,iy=0,iside=1):
        Shape.__init__(self,ix,iy)
        self.side=iside

    def draw(self,turt):
        turt.pu()
        turt.goto(self.x,self.y)
        turt.pd()
        if self.fill==True:
            turt.fillcolor(self.color)
            turt.begin_fill()
            for i in range(3):
                turt.fd(self.side)
                turt.right(120)
            turt.end_fill()
        else:
            for i in range(3):
                turt.fd(self.side)
                turt.right(60)

    def isIN(self,nx,ny):
        if nx<=(self.x+self.side) and nx>=self.x:
            if ny>=(self.y-self.side) and ny<=(self.y):
                return True
        return False

class Square(Shape):
    def __init__(self,ix=0,iy=0,iside=1):
        Shape.__init__(self,ix,iy)
        self.side=iside

    def draw(self,turt):
        turt.pu()
        turt.goto(self.x,self.y)
        turt.pd()
        if self.fill==True:
            turt.fillcolor(self.color)
            turt.begin_fill()
            for i in range(4):
                turt.fd(self.side)
                turt.right(90)
            turt.end_fill()
        else:
            for i in range(2):
                turt.fd(self.side)
                turt.right(90)

    def isIN(self,nx,ny):
        if nx<=(self.x+self.side) and nx>=self.x:
            if ny>=(self.y-self.side) and ny<=(self.y):
                return True
        return False
