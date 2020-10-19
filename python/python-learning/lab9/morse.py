def morseTranslate(sent,morse):
    for char in sent:
        if char=='.':
            print("\n")
        elif char==' ':
            print("")
        else:
            print(morse[char.upper()])


def main():
    morseDict={'A':". _",'B':"_ . . .",'C':"_ . _ .",'D':"_ . .",'E':".",
        'F':". . _ .",'G':"_ _ .",'H':". . . .",'I':". .",'J':". _ _ _",
        'K':"_ . _",'L':". _ . .",'M':"_ _",'N':"_ .",'O':"_ _ _",
        'P':". _ _ .",'Q':"_ _ . _",'R':". _ .",'S':". . .",
        'T':"_",'U':". . _",'V':". . . _",'W':". _ _",
        'X':"_ . . _",'Y':"_ . _ _",'Z':"_ _ . ."}
    go='y'
    while go.lower()=='y':
        sentence=input("Enter a word, phrase, or sentence: ")
        morseTranslate(sentence,morseDict)
        go=input("Another? y/n: ")

if __name__=='__main__':
    main()
