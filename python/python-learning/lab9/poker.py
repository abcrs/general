def rankandSuitCount(cards):
    rank={}
    suit={}
    for i in cards:
        rank[i[0]]=rank.get(i[0],0)+1
        suit[i[1]]=suit.get(i[1],0)+1
    return rank,suit

def findStraight(ranks):
    cardList=[]
    for i in ranks:
        if i.upper()=='T':
            cardList.append(10)
        elif i.upper()=='J':
            cardList.append(11)
        elif i.upper()=='Q':
            cardList.append(12)
        elif i.upper()=='K':
            cardList.append(13)
        elif i.upper()=='A':
            cardList.append(14)
        else:
            cardList.append(int(i))
    cardList.sort()
    if cardList[3]==5 and cardList[4]==14:
        return 1
    for j in range(len(cardList)-1):
        if (cardList[j+1]-cardList[j])>1:
            return 0
    return 1

def pokerHand(cards):
    rank,suit=rankandSuitCount(cards)
    if len(rank)==5:
        straight=findStraight(rank)
        if straight==1 and len(suit)==1:
            return "straight flush"
        elif straight==1:
            return "straight"
        elif len(suit)==1:
            return "flush"
        return "high-card"
    elif len(rank)==4:
        return "one pair"
    elif len(rank)==3:
        for j in rank:
            if rank[j]==3:
                return "three-of-a-kind"
        return "two pair"
    elif len(rank)==2:
        for k in rank:
            if rank[k]==4:
                return "four-of-a-kind"
        return "full house"

def main():
    go='y'
    while go.lower()=='y':
        hand=input("Enter a hand of cards: ")
        hand=hand.split(" ")
        print(pokerHand(hand))
        go=input("Another? y/n: ")

if __name__=='__main__':
    main()
