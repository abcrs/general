def addDB(data,name,num):
    if name in data:
        data[name].append(num)
    else:
        data[name]=[num]
    if num in data:
        data[num].append(name)
    else:
        data[num]=[name]

def findDB(data,key):
    keylist=[]
    for i in data:
        if i==key:
            return data[i]
    return []

def removeDB(data,name,num):
    for i in data:
        if i==name:
            if num in data[name]:
                data[name].remove(num)
        if i==num:
            if name in data[num]:
                data[num].remove(name)

def main():
    data={}
    com=[0]
    while com[0]!="end":
        com=input("-->")
        com=com.split(" ")
        if com[0]=="add":
            addDB(data,com[1],com[2])
        elif com[0]=="find":
            print(findDB(data,com[1]))
        elif com[0]=="del":
            removeDB(data,com[1],com[2])
        elif com[0]=="clear":
            data={}
        elif com[0]=="end":
            break
        else:
            print("That is not a valid command. Please re-enter.")


if __name__=='__main__':
    main()
