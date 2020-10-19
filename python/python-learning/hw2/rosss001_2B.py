#CSCI 1133 Homework 2
#Anthony Ross-Sapienza
#Problem B

def findSign(day,mon):
    if mon==1:
        if day<=19:
            return "Capricorn"
        else:
            return "Aquarius"
    elif mon==2:
        if day<=18:
            return "Aquarius"
        else:
            return "Pisces"
    elif mon==3:
        if day<=20:
            return "Pisces"
        else:
            return "Aries"
    elif mon==4:
        if day<=19:
            return "Aries"
        else:
            return "Taurus"
    elif mon==5:
        if day<=20:
            return "Taurus"
        else:
            return "Gemini"
    elif mon==6:
        if day<=20:
            return "Gemini"
        else:
            return "Cancer"
    elif mon==7:
        if day<=22:
            return "Cancer"
        else:
            return "Leo"
    elif mon==8:
        if day<=22:
            return "Leo"
        else:
            return "Virgo"
    elif mon==9:
        if day<=22:
            return "Virgo"
        else:
            return "Libra"
    elif mon==10:
        if day<=22:
            return "Libra"
        else:
            return "Scorpio"
    elif mon==11:
        if day<=21:
            return "Scorpio"
        else:
            return "Sagittarius"
    elif mon==12:
        if day<=21:
            return "Sagittarius"
        else:
            return "Capricorn"


def main():
    while True:
        month=int(input("Month of birth: "))
        date=int(input("Day of birth: "))
        if date<=0 or month<=0 or month>12 or date>31:
            print("Invalid date")
        elif month==2:
            if date>28:
                print("Invalid date")
            else:
                break
        elif month==4 or month==6 or month==9 or month==11:
            if date>30:
                print("Invalid date")
            else:
                break
        else:
            break

    sign=findSign(date,month)
    print(sign)


if __name__=='__main__':
    main()
