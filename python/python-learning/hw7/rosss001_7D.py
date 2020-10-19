#CSCI 1133 Homework 7
#Anthony Ross-Sapienza
#Problem D

def crime_report(fnameCSV):
    f=open(fnameCSV,'r')
    burg={}
    thef={}
    robb={}
    for line in f:
        temp=line                                           #Each line is read
        temp=temp.split(',')                                #And separated into a list, split by commas
        if "BURGLARY" in temp[5]:                           #If BURGLARY is found in the crime description column
            if temp[2] in burg:
                burg[temp[2]]+=1                            #That district either increases its crime stat
            else:
                burg[temp[2]]=1                             #Or starts it, if it's the first such crime in the report in that district
        if "THEFT" in temp[5]:
            if temp[2] in thef:                             #Repeated for THEFT
                thef[temp[2]]+=1
            else:
                thef[temp[2]]=1
        if "ROBBERY" in temp[5]:                            #And ROBBERY
            if temp[2] in robb:
                robb[temp[2]]+=1
            else:
                robb[temp[2]]=1
    f.close()
    outf=open("stealingOffenses.txt",'w')
    outf.write("Burglaries by District:\n")
    for i in range(1,len(burg)+1):
        outf.write(str(i)+": "+str(burg[str(i)])+"\n")
    outf.write("\nThefts by District:\n")
    for j in range(1,len(thef)+1):
        outf.write(str(j)+": "+str(thef[str(j)])+"\n")
    outf.write("\nRobberies by District:\n")
    for k in range(1,len(robb)+1):
        outf.write(str(k)+": "+str(robb[str(k)])+"\n")
    outf.close()
