class vec3:
    def __init__(self,alist=None):
        if alist==None:
            self.vector=[0,0,0]
        else:
            self.vector=[alist[0],alist[1],alist[2]]
            
    def __str__(self):
        return '['+str(self.vector[0])+", "+str(self.vector[1])+", "+str(self.vector[2])+']'

    def vlist(self):
        return [self.vector[0],self.vector[1],self.vector[2]]

    def setValues(self, addvec):
        self.vector[0]+=addvec[0]
        self.vector[1]+=addvec[1]
        self.vector[2]+=addvec[2]

    def __float__(self):
        return (self.vector[0]**2+self.vector[1]**2+self.vector[2]**2)**.5

    def __add__(self,other):
        nx=self.vector[0]+other.vector[0]
        ny=self.vector[1]+other.vector[1]
        nz=self.vector[2]+other.vector[2]
        return vec3([nx,ny,nz])

    def __truediv__(self,scale):
        nx=self.vector[0]/scale
        ny=self.vector[1]/scale
        nz=self.vectpr[2]/scale
        return vec3([nx,ny,nz])

def main():
    v1=input("Enter the values of the first vector separated by a space: ")
    v2=input("Enter the values of the second vector separated by a space: ")
    v1=(v1.split(' '))
    v2=(v2.split(' '))
    ve1=vec3([int(v1[0]),int(v1[1]),int(v1[2])])
    ve2=vec3([int(v2[0]),int(v2[1]),int(v2[2])])
    mass=int(input("Enter the mass value: "))
    avec=ve2+ve1
    aval=avec/mass
    print(aval)
    print(float(avec))

if __name__=='__main__':
    main()
