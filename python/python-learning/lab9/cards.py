def rankandSuitCount(cards):
    rank={}
    suit={}
    for i in cards:
        rank[i[0]]=rank.get(i[0],0)+1
        suit[i[1]]=suit.get(i[1],0)+1
    return rank, suit
