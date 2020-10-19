#Anthony Ross-Sapienza
#CSCI 1133
#Problem 5A
def flattenList(alist):
    if len(alist)==0:                           #Can just return an empty list
            return []                           #When added to the main list, it will just disappear
    elif len(alist)==1:
        if type(alist[0])!=list:                #A list of length one that does not contain a list
            return alist                        #Is the base case
        else:
            return flattenList(alist[0])
    elif type(alist[0])!=list:                  #If the first element of is not a list
        return alist[:1]+flattenList(alist[1:]) #Move on to the rest of the list
    else:
        return flattenList(alist[0])+flattenList(alist[1:])
