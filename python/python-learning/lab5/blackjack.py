def blackScore(hand):
    test=0
    score=0
    for i in range(len(hand)):
        if hand[i]=='T' or hand[i]=='J' or hand[i]=='Q' or hand[i]=='K':
            score+=10
        elif hand[i]=='A':
            score+=11
            test+=1
        elif int(hand[i])>=2 or int(hand[i])<=9:
            score+=int(hand[i])
    while score>21 and test>0:
        score-=10
        test-=1
    return score

def main():
    hand=input("Enter a hand: ")
    score=blackScore(hand)
    print(str(score))

if __name__=='__main__':
    main()
