import random

def makeDeck(newdeck):
    limit=52
    suit=1
    while limit>0:
        newdeck.append(suit)
        suit+=1
        if suit>13:
            suit=1
        limit-=1
    random.shuffle(newdeck)

def main():
    deck=[]
    makeDeck(deck)
    hand=[]
    scoreList=[0,0,0,0,0,0,0]
    go=1
    deckcount=0
    for i in range(10):
        go=1
        hand=[]
        while go==1:
            if deckcount==52:
                deckcount=0
                random.shuffle(deck)
            hand.append(deck[deckcount])
            score=checkScore(hand)
            if score>17:
                if score<22:
                    score-=17
                    scoreList[score]+=1
                if score>22:
                    scoreList[6]+=1
        deckcount+=1


if __name__=='__main__':
    main()
