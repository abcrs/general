def checkWord(newword):
    first=newword[0]
    for i in range(1,len(newword)):
        if newword[i].lower()==first.lower():
            return True
    return False

def main():
    wordList=[]
    go=1
    check=False
    while go==1:
        word=input("Enter a new word: ")
        if word=="":
            go=0
        else:
            check=checkWord(word)
        if check==True:
            wordList.append(word)
    for i in range(len(wordList)):
        print(str(wordList[i]))

if __name__=='__main__':
    main()
