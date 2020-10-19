def mysplit(stringarg,delimiter):
    splits=[]
    idx=0
    base=0
    count=0
    delim=len(delimiter)
    while count<len(stringarg):
        idx=stringarg.find(delimiter,base)
        if idx>0:
            splits.append(stringarg[base:idx])
            base=idx+delim
        else:
            splits.append(stringarg[base:])
            count=len(stringarg)
        count+=1
    return splits
