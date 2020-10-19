#Anthony Ross-Sapienza
#CSCI 1133 Final Project
import turtle

class County():
    def __init__(self,name,data):
        self.nameCS=name
        self.slope=0
        self.intercept=0
        self.poplist=data
        slopeL=[-1/7,-3/35,-1/35,1/35,3/35,1/7]
        interL=[11/21,8/21,5/21,2/21,-1/21,-4/21]
        for i in range(len(self.poplist)):
            self.slope+=self.poplist[i]*slopeL[i]               #The slope and intercept are kept to use in other methods
            self.intercept+=self.poplist[i]*interL[i]

    def __lt__(self,rhand):                                     #Simple check for which slope is greater
        if self.slope<rhand.slope:
            return True
        return False

    def drawSlope(self,scale):
        startY=(self.intercept/scale)-300                       #The slope is drawn the same for Counties and States, so it can be a different method that State can inherit
        endY=((5*self.slope+self.intercept)/scale)-300
        turtle.goto(-300,startY)
        turtle.pensize(2)
        turtle.pd()
        turtle.goto(250,endY)
        turtle.pu()
        written="y = {:.4f}x + {:.4f}".format(self.slope,self.intercept)
        turtle.write(written,font=("Arial",12,"normal"))

    def display(self,y_max=200):
        turtle.color("red")
        turtle.speed(0)
        turtle.ht()
        x=-300
        countyScale=max(self.poplist)/y_max                     #The scale is based off of the y_max and the county's max population
        for pop in self.poplist:
            turtle.pu()
            turtle.goto(x,pop/countyScale-300)
            turtle.dot(10)                                      #Dots are drawn at each population for the years
            x+=110
        self.drawSlope(countyScale)                             #The slope is drawn in another function
        turtle.goto(-25,230)
        turtle.write(self.nameCS,font=("Arial",15,"normal"))

    def getName(self):
        return self.nameCS

class State(County):
    def __init__(self,name,data):
        super().__init__(name,data)
        self.stateScale=max(self.poplist)/500
        self.countyList=[]

    def addCounty(self,county):
        self.countyList.append(county)

    def drawAxes(self):                                     #The axes are drawn in a separate method, just to keep the display method clean
        turtle.pensize(1)
        turtle.pu()
        turtle.goto(-310,-300)
        turtle.seth(0)
        turtle.color("black")
        turtle.pd()
        turtle.fd(560)
        turtle.pu()
        turtle.goto(-300,-310)
        turtle.seth(90)
        turtle.pd()
        turtle.fd(520)
        turtle.pu()
        turtle.seth(90)
        for xname in range(0,6):
            turtle.goto(-310+xname*110,-325)
            turtle.write(str(2010+xname),font=("Arial",9,"normal"))
        for xtick in range(0,5):
            turtle.goto(-190+110*xtick,-310)
            turtle.pd()
            turtle.fd(20)
            turtle.pu()
        turtle.seth(0)
        for ytick in range(0,4):
            turtle.goto(-310,-175+ytick*125)
            turtle.pd()
            turtle.fd(20)
            turtle.pu()
        for yname in range(1,5):
            turtle.goto(-370,-310+yname*125)
            written="{:.0f}".format(max(self.poplist)/4*yname)
            turtle.write((written),font=("Arial",9,"normal"))

    def display(self):                                          #Because County has a method to get the scale, and a different pen color, the display method has to be overwritten
        turtle.speed(0)
        turtle.ht()
        self.drawAxes()
        turtle.color("blue")
        x=-300
        for pop in self.poplist:
            turtle.pu()
            turtle.goto(x,pop/self.stateScale-300)
            turtle.dot(10)
            x+=110
        self.drawSlope(self.stateScale)                         #The same code for the slope can be used for both classes
        turtle.goto(-25,250)
        turtle.write(self.nameCS,font=("Arial",20,"bold"))

class Analysis():
    def __init__(self,stateL):
        self.stateList=stateL

    def displayState(self,name):
        for states in self.stateList:
            if name.lower()==states.getName().lower():
                states.display()

    def displayStateGreatestCounty(self,name):
        for i in self.stateList:
            if name==i.getName():
                state=i
        highCounty=state.countyList[0]
        for j in state.countyList:
            if highCounty<j:
                highCounty=j
        y_max=max(highCounty.poplist)/state.stateScale
        state.display()
        highCounty.display(y_max)

    def displayStateLeastCounty(self,name):
        for i in self.stateList:
            if name==i.getName():
                state=i
        lowCounty=state.countyList[0]
        for j in state.countyList:
            if j<lowCounty:
                lowCounty=j
        y_max=max(lowCounty.poplist)/state.stateScale
        state.display()
        lowCounty.display(y_max)

    def clear(self):
        turtle.clear()

    def greatestState(self):
        highState=self.stateList[0]
        for i in self.stateList:
            if highState<i:
                highState=i
        name=highState.getName()
        return name

    def leastState(self):
        lowState=self.stateList[0]
        for i in self.stateList:
            if i<lowState:
                lowState=i
        name=lowState.getName()
        return name

inf=open("censusdata.csv",'r')
stateL=[]
inf.readline()
for line in inf:
    line=line.split(",")
    popList=list(map(int,line[1:]))                             #The populations for the State/County are converted to integers and put in a list
    if "county" not in line[0].lower():
        state=State(line[0],popList)                            #There is a variable for each state that doesn't change until the next state comes up in the data
        stateL.append(state)
    else:
        county=County(line[0],popList)
        state.addCounty(county)                                 #And so each county can be added to that State's list
analysis=Analysis(stateL)
inf.close()
