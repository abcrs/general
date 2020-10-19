#CSCI 1133 Homework 2
#Anthony Ross-Sapienza
#Problem D

def whoWins(p1,p2):
    if p1.lower()=="r":
        if p2.lower()=="r":
            return 3
        elif p2.lower()=="p":
            return 2
        elif p2.lower()=="s":
            return 1
    elif p1.lower()=="p":
        if p2.lower()=="r":
            return 1
        elif p2.lower()=="p":
            return 3
        elif p2.lower()=="s":
            return 2
    elif p1.lower()=="s":
        if p2.lower()=="r":
            return 2
        elif p2.lower()=="p":
            return 1
        elif p2.lower()=="s":
            return 3

def main():
    loop=1
    p1win=0
    p1temp=""
    p2win=0
    p2temp=""
    winner=0
    while loop<=3:
        print("Round # "+str(loop))
        p1temp=input("Player 1's Choice ")
        p2temp=input("Player 2's Choice ")
        winner=whoWins(p1temp,p2temp)
        if winner==1:
            print("Player 1 wins this round")
            p1win+=1
        elif winner==2:
            print("Player 2 wins this round")
            p2win+=1
        elif winner==3:
            print("No one wins this round")
        loop+=1
    if p1win>p2win:
        print('\n'+'\n'+"Player 1 wins the game")
    elif p2win>p1win:
        print('\n'+'\n'+"Player 2 wins the game")
    elif p1win==p2win:
        print('\n'+'\n'+"It is a tie!")


if __name__=='__main__':
    main()
