#CSCI 1133 Homework 3
#Anthony Ross-Sapienza
#Problem D

def winCheck(mark,board):
    for i in range(0,2):                    #Check for horizontal winners
        if board[i][0]==mark:
            if board[i][1]==mark and board[i][2]==mark:
                return mark
    for j in range(0,2):                    #Check for vertical winners
        if board[0][j]==mark:
            if board[1][j]==mark and board[2][j]==mark:
                return mark
    if board[1][1]==mark:                   #Check for diagonal winners
        if (board[0][0]==mark and board[2][2]==mark) or (board[2][0]==mark and board[0][2]==mark):
            return mark
    return ""

def printBoard(board):
    for i in board:
        print(i)

def makePlay(turn):
    if turn%2==0:
        newMove=int(input("Player 1, where would you like to move? "))
    else:
        newMove=int(input("Player 2, where would you like to move? "))
    return newMove

def checkMove(location,board,piece):        #This function checks if a spot is open
    if location==0:                         #If it's open, if replaces the spot with the player's piece
        if board[0][0]==" ":                #If it's not, it returns a -1, which asks the player to select again
            board[0][0]=piece               #Values not between 0 and 8 also return a -1, so while no error message is displayer
            return 0                        #The game continues on (and that player's turn is skipped)
        else:
            return -1
    elif location==1:
        if board[0][1]==" ":
            board[0][1]=piece
            return 0
        else:
            return -1
    elif location==2:
        if board[0][2]==" ":
            board[0][2]=piece
            return 0
        else:
            return -1
    elif location==3:
        if board[1][0]==" ":
            board[1][0]=piece
            return 0
        else:
            return -1
    elif location==4:
        if board[1][1]==" ":
            board[1][1]=piece
            return 0
        else:
            return -1
    elif location==5:
        if board[1][2]==" ":
            board[1][2]=piece
            return 0
        else:
            return -1
    elif location==6:
        if board[2][0]==" ":
            board[2][0]=piece
            return 0
        else:
            return -1
    elif location==7:
        if board[2][1]==" ":
            board[2][1]=piece
            return 0
        else:
            return -1
    elif location==8:
        if board[2][2]==" ":
            board[2][2]=piece
            return 0
        else:
            return -1

def main():
    player=""
    winner=""
    turn=0
    gameBoard=[[" "," "," "],[" "," "," "],[" "," "," "]]
    while winner=="":
        move=-1
        if turn%2==0:
            player="x"
        else:
            player="o"
        while move==-1:
            move=makePlay(turn)
            move=checkMove(move,gameBoard,player)
            if move==-1:
                print("Sorry, that space is already taken.")
            printBoard(gameBoard)
        winner=winCheck(player,gameBoard)
        turn+=1
        if turn==9:                     #When the 9th turn is played, it is automatically a tie.
            winner="t"
    if winner=="x":
        print("Player 1 wins!")
    elif winner=="o":
        print("Player 2 wins!")
    elif winner=="t":
        print("It's a tie. That's too bad.")

if __name__=='__main__':
    main()
