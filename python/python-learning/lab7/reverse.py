def reverse(istring):
    revstring=""
    count=len(istring)-1
    while count>=0:
        revstring+=istring[count]
        count-=1
    return revstring
