#CSCI 1133 Homework 4
#Anthony Ross-Sapienza
#Problem C

def merge2(sentence1,sentence2):
    sent1=sentence1.split(' ')
    sent2=sentence2.split(' ')
    sentCombo=[]
    newSent=""
    go=0
    top=len(sent1)+len(sent2)
    while go<top:
        if sent1==[]:
            for j in sent2:
                sentCombo.append(j)
            break
        if sent2==[]:
            for k in sent1:
                sentCombo.append(k)
            break
        if go%2==0:
            sentCombo.append(sent1[0])
            sent1.remove(sent1[0])
            if sent1!=[]:
                sentCombo.append(sent1[0])
                sent1.remove(sent1[0])
        else:
            sentCombo.append(sent2[0])
            sent2.remove(sent2[0])
            if sent2!=[]:
                sentCombo.append(sent2[0])
                sent2.remove(sent2[0])
        go+=1
    for i in range(len(sentCombo)):
        if i<top-1:
            newSent=newSent+str(sentCombo[i])+" "
        else:
            newSent=newSent+str(sentCombo[i])
    return newSent
