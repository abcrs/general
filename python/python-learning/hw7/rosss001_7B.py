#CSCI 1133 Homework 7
#Anthony Ross-Sapienza
#Problem B

class Member():
    def __init__(self,iinstrument,iname):
        self.name=iname
        self.instrument=iinstrument

    def getInstrument(self):
        return self.instrument

    def getPlayer(self):
        return self.name

    def setInstrument(self,instrument):
        self.instrument=instrument

    def setPlayer(self,player):
        self.name=player

    def __str__(self):
        return self.name+" plays "+self.instrument

    def __eq__(self,rhand):
        if self.name.lower()==rhand.name.lower() and self.instrument.lower()==rhand.instrument.lower():
            return True
        return False

class Band():
    def __init__(self,bandname,memberlist):
        self.bname=bandname
        self.members=memberlist

    def getBandName(self):
        return self.bname

    def getPlayers(self):
        memname=[]
        for member in self.members:
            memname.append(member.getPlayer())
        return memname

    def getInstruments(self):
        meminst={}
        for member in self.members:
            if member.getInstrument().lower() in meminst:
                meminst[member.getInstrument().lower()]+=1
            else:
                meminst[member.getInstrument().lower()]=1
        return meminst

    def addMember(self,member):
        self.members.append(member)

    def removeMember(self,member):
        removeList=[]
        for i in range(len(self.members)):
            if self.members[i]==member:
                removeList.append(i)
        removeList.reverse()
        for j in removeList:
            self.members.pop(j)

    def __str__(self):
        bandprint="Members of "+self.bname+":"
        if len(self.members)==0:
            bandprint+="\nOh no, the band is empty!"                    #A special message for an empty band, because that doesn't seem right!
        else:
            for member in self.members:
                bandprint+="\n"+member.__str__()
        return bandprint

    def findPlayer(self,player):
        nothere=True
        for member in self.members:
            if player.lower()==member.getPlayer().lower():
                print(member)
                nothere=False
        if nothere==True:
            print(self.bname,"does not have any players named",player)

    def findInstrument(self,instrument):
        nothere=True
        for member in self.members:
            if instrument.lower()==member.getInstrument().lower():
                print(member)
                nothere=False
        if nothere==True:
            print(self.bname,"does not have any",instrument,"players")
