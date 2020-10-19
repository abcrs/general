def reverse(istring):
    revstring=""
    count=len(istring)-1
    while count>=0:
        revstring+=istring[count]
        count-=1
    return revstring

def ispalindrom(string1,string2):
    first=""
    second=""
    for ch in string1:
        if ch.isalpha():
            first+=ch.lower()
    for ch2 in string2:
        if ch2.isalpha():
            second+=ch2.lower()
    return first==second


def main():
    go=True
    check=""
    rev=""
    while go:
        check=input("Enter a string: ")
        rev=reverse(check)
        ispali=ispalindrom(check,rev)
        if ispali:
            print(check+" is a palindrome.")
        else:
            print(check+" is not a palindrome.")
        yn=input("Continue? (y/n): ")
        if yn=="n":
            go=False


if __name__=='__main__':
    main()
