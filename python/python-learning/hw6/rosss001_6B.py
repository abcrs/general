#CSCI 1133 Homework 6
#Anthony Ross-Sapienza
#Problem B

def parse_string(string):
    bore=["to","the","and","i","of","he","she","a","i'll","i've","but","by","we","whose","how","go","such","this","me","can","she's","he's","have","has","had","an","did","so","to","we'll","on","him","well","or","be","as","those","there","are","do","too","if","it","at","what","that","you","will","in","with","not","for","is","my","o","her","his","am"]
    string=string.split()
    funstring=[]                                                    #This list will hold all non-boring words
    wcount={}                                                       #The dictionary that will be filled
    noword=0                                                        #This will count any empty strings
    for y in range(0,len(string)):
        if string[y].lower() not in bore:                           #This loop removes boring words
            funstring.append(string[y])
    for x in range(0,len(funstring)):
        for char in funstring[x]:
            if char.lower() not in "abcdefghijklmnopqrstuvwxyz":    #This removes all non-alphabetical characters
                funstring[x]=funstring[x].replace(char,"")
                if funstring[x]=="":
                    noword+=1                                       #If empty strings exist, this counts them
    while noword>0:
        funstring.remove("")                                        #And this loop removes them
        noword-=1
    for word in funstring:
        if word.lower() in wcount:
            wcount[word.lower()]+=1
        else:
            wcount[word.lower()]=1
    for key in wcount:
        print(key,end=" ")
        time5=wcount[key]//5                                        #This checks if the word has been used 5 or more times
        time1=wcount[key]%5
        for i in range(0,time5):
            print("X ",end="")
        for j in range(0,time1):
            print("* ",end="")
        print("")
