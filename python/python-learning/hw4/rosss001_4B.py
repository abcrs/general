#CSCI 1133 Homework 4
#Anthony Ross-Sapienza
#Problem B

def wordRepeater(aList):
    words=[]                                #Sets a list to hold the unique words
    for i in range(len(aList)):
       if aList[i].lower() not in words:    #Finds if a word is already in list
            print(aList[i],end=' ')         #If not, prints word then searches
            for j in range(i,len(aList)):   #For each instance of the word, prints the index
                if aList[j]==aList[i]:
                    print(j,end=' ')
            words.append(aList[i])          #Adds the word to the list so it isn't repeated
            print('')

def main():
    go='y'
    while (go.lower()=='y'):
        sent=input("Enter a sentence: ")
        sentList=sent.lower().split(' ')
        wordRepeater(sentList)
        go=input("Do you want to enter another sentence (Y/N)? ")

if __name__=='__main__':
    main()
