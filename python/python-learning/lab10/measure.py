class measure:
    def __init__(self,ifeet=0,iinch=None):
        if iinch==None:
            self.inch=ifeet%12
            ifeet=ifeet/12
        elif iinch>12:
            self.inch=iinch%12
            ifeet+=iinch//12
        else:
            self.inch=iinch
        self.feet=ifeet

    def __str__(self):
        if self.feet>0 and self.inch>0:
            return str(self.feet)+"' "+str(self.inch)+'"'
        elif self.feet>0 and self.inch==0:
            return str(self.feet)+"'"
        elif self.feet==0:
            return str(self.inch)+'"'

    def __add__(self,other):
        newf=self.feet+other.feet
        newi=self.inch+other.inch
        return measure(newf,newi)

    def __sub__(self,other):
        newf=self.feet-other.feet
        newi=self.inch-other.inch
        if newi<1:
            newf-=1
            newi+=12
        return measure(newf,newi)
