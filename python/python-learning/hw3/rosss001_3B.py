#CSCI 1133 Homework 3
#Anthony Ross-Sapienza
#Problem B

def foodCheck(item,price):
    if "burger" in item:
        price+=3
        return price
    elif "soda" in item:
        price+=2
        return price
    else:
        price+=5
        return price

def main():
    order=[]
    total=0
    print("Welcome to the Python Buffet, the most snake-like restaurant in town!\n")
    food=input("What would you like to order? ")
    while food!="":
        dup=0
        for i in order:
            if food in i:
                print("Oops. You must have entered "+food+" again by accident.")
                dup=1
        if dup==0:
            order.append(food)
            total=foodCheck(food,total)
        food=input("Would you like to order anything else? ")
    print("You have ordered the following:")
    for i in range(len(order)):
        print(order[i])
    total=format(total,".2f")
    print("This will cost you a total of $"+total)
    print("Thank you for your patronage!")


if __name__=='__main__':
    main()
