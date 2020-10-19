def ltrcount(istring):
    count=0
    for ch in istring:
        if ch.isalpha():
            count+=1
    return count
