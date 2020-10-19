def genefinder(istring):
    genes=[]
    idx=0
    base=0
    count=0
    while count<len(istring):
        idx=istring.find("ATG",base)
        base=idx+3
        if idx>0:
            print("test1")
            tag=istring.find("TAG",base)
            if tag<0:
                tag=len(istring)+1
            taa=istring.find("TAA",base)
            if taa<0:
                taa=len(istring)+1
            tga=istring.find("TGA",base)
            if tga<0:
                tga=len(istring)+1
            if tag<taa and tag<tga:
                if istring[base,tag]%3==0:
                    print("test2")
                    genes.append(istring[base:tag])
                    base=tag+3
            if taa<tag and taa<tga:
                if istring[base,taa]%3==0:
                    genes.append(istring[base:taa])
                    base=tag+3
            if tga<tag and tga<taa:
                if len(istring[base:tga])%3==0:
                    print("Test3")
                    genes.append(istring[base:tga])
                    base=tag+3
        else:
            count=len(istring)
        count+=1
    return genes

def main():
    seq=input("Enter a DNA sequence: ")
    count=1
    gene=genefinder(seq)
    for i in range(len(gene)):
        print("Gene "+str(count)+" "+gene[i])
        count+=1

if __name__=='__main__':
    main()
