#CSCI 1133 Homework 1
#Anthony Ross-Sapienza
#Problem 1B
euroCon=.83
yenCon=111.14
bitCon=.000076
print("Welcome tot he Current Conversion Program!")
dollar=float(input("Enter an amount in U.S. Dollars: $ "))
euro=format(dollar*euroCon,".2f")
yen=format(dollar*yenCon,".2f")
bitcoin=format(dollar*bitCon,".2f")
dollar=format(dollar,".2f")
print("$ "+dollar+" = "+euro+" euro")
print("$ "+dollar+" = "+yen+" yen")
print("$ "+dollar+" = "+bitcoin+" bitcoin")
