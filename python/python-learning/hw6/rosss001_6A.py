#CSCI 1133 Homework 6
#Anthony Ross-Sapienza
#Problem A

FOOD={"pizza":127829,"chicken":127831,"apple":127822,"peach":127825,"cherry":127826,"yam":127840,"pineapple":127821,"cookie":127850,"bread":127838,"lemon":127819,"banana":127820,"strawberry":127827}

def lookup(d,item):
    if item in d:
        print(item,end=" ")
        if item in FOOD:                            #If the item isn't in the food dictionary
            for amount in range(d[item]):           #This step is skipped
                print(chr(FOOD[item]),end="")
        else:
            print(str(d[item]),end="")              #And just the value is printed out
        print("")

def show(d):
    for item in d:
        print(item,end=" ")
        if item in FOOD:
            for amount in range(d[item]):
                print(chr(FOOD[item]),end="")
        else:
            print(str(d[item]),end="")
        print("")

def addItem(d,item):
    if item in d:
        d[item]+=1
    else:
        d[item]=1

def subItem(d,item):
    if item in d:
        d[item]-=1
        if d[item]==0:
            del d[item]
    else:
        return

def main():
    cart={}
    control=""
    while control!="quit":
        control=input("=> ")
        control=control.split(" ")
        if control[0].lower()=="lookup":
            lookup(cart,control[1].lower())
        elif control[0].lower()=="show":
            show(cart)
        elif control[0].lower()=="add":
            addItem(cart,control[1].lower())
        elif control[0].lower()=="sub":
            subItem(cart,control[1].lower())
        elif control[0].lower()=="quit":
            control="quit"

if __name__=='__main__':
    main()
