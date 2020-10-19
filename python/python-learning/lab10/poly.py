class poly:
    def __init__(self,coeff=None):
        if coeff==None:
            self.coef=[0]
        else:
            self.coef=coeff

    def degree(self):
        if len(self.coef)==0:
            if self.coef[0]==0:
                return 0
            else:
                return 1
        else:
            return len(self.coef)

    def addTerm(self,val,exp):
        z0=exp-len(self.coef)
        while z0>1:
            self.coef.append(0)
        self.coef.append(val)

    def __str__(self):
        term=len(self.coef)-1
        out=""
        while term>=0:
            if self.coef[term]==0:
                term-=1
            elif self.coef[term]==1 or self.coef[term]==-1:
                if term>1:
                    if self.coef[term]==1 and out=="":
                        out+='x'
                    elif self.coef[term]==-1 and out=="":
                        out+="-x"
                    elif self.coef[term]==1 and out!="":
                        out+="+ x"
                    else:
                        out+="- x"
                    out+='^'+str(term)+' '
                elif term==1:
                    if self.coef[term]==1 and out=="":
                        out+='x '
                    elif self.coef[term]==-1 and out=="":
                        out+="-x "
                    elif self.coef[term]==1 and out!="":
                        out+="+ x "
                    else:
                        out+="- x "
                else:
                    if self.coef[term]==1 and out=="":
                        out+='1'
                    elif self.coef[term]==-1 and out=="":
                        out+="-1"
                    elif self.coef[term]==1 and out!="":
                        out+="+ 1 "
                    else:
                        out+="- 1 "
                term-=1
            else:
                if term>1:
                    if out=="" and self.coef[term]>0:
                        out+=str(self.coef[term])+'x'
                    elif out=="" and self.coef[term]<0:
                        out+="-"+str(abs(self.coef[term]))+'x'
                    elif self.coef[term]>0:
                        out+="+ "+str(self.coef[term])+'x'
                    else:
                        out+="- "+str(abs(self.coef[term]))+'x'
                    out+='^'+str(term)+' '
                elif term==1:
                    if out=="" and self.coef[term]>0:
                        out+=str(self.coef[term])+"x "
                    elif out=="" and self.coef[term]<0:
                        out+="-"+str(abs(self.coef[term]))+"x "
                    elif self.coef[term]>0:
                        out+="+ "+str(self.coef[term])+"x "
                    else:
                        out+="- "+str(abs(self.coef[term]))+"x "
                else:
                    if out=="" and self.coef[term]>0:
                        out+=str(self.coef[term])
                    elif out=="" and self.coef[term]<0:
                        out+="-"+str(abs(self.coef[term]))
                    elif self.coef[term]>0:
                        out+="+ "+str(self.coef[term])
                    else:
                        out+="- "+str(abs(self.coef[term]))
                term-=1
        return out
