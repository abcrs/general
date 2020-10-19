#CSCI 1133 Homework 7
#Anthony Ross-Sapienza
#Problem C

def mine_file(fname):
    f=open(fname,'r')
    uniquewords={}                                      #The dictionary to hold the uniquewords
    wordcount=0                                         #This will keep track of the word count throughout the lines
    apost=0                                             #Apostrophe word count
    highword=0                                          #This will track the word with the highest count throughout the text
    for line in f:
        temp=line                                       #A temp variable is created to hold each line
        for i in range(len(temp)):                      #Replaces all punction with a blank space, splitting words separated by dashes/hypens
            for punc in "!?.,;:-":
                if temp[i]==punc:
                    temp=temp.replace(punc," ")
        temp=temp.split()                               #Temp is split by blank spaces now, to be counted
        for word in temp:                               #Each word in temp is checked
            if word.lower() in uniquewords:
                uniquewords[word.lower()]+=1            #And either increases an existing dictionary key
            else:
                uniquewords[word.lower()]=1             #Or creates a new
            if uniquewords[word.lower()]>highword:      #If the word has a higher than the previous highest count, it now has the highest count
                highword=uniquewords[word.lower()]
            for char in word:
                if char=="'":                           #Counts the apostrophe words
                    apost+=1
        wordcount+=len(temp)                            #Increases the word count at the end of each line
    f.close()
    print("Word Count:",str(wordcount))
    print("Unique Word Count:",str(len(uniquewords)))
    print("Apostrophe Word Count:",str(apost))
    while highword>4:
        for word in uniquewords:                        #Iterates through the dictionary and finds the words with the highest counts
            if uniquewords[word]==highword:
                print(word+":",str(highword))           #Then prints them out
        highword-=1
