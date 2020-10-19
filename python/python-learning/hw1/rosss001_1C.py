#CSCI 1133 Homework 1
#Anthony Ross-Sapienza
#Problem 1C
import turtle
import math
width=float(input("Enter a width: "))
height=float(input("Enter a height: "))
hypo=math.hypot(width,height)
angle=math.asin(height/hypo)*180/math.pi
turtle.fd(width)
turtle.left(90)
turtle.fd(height)
turtle.left(90)
turtle.fd(width)
turtle.left(90)
turtle.fd(height)
turtle.left(90)
turtle.pu()
turtle.fd(width*2)
turtle.pd()
turtle.fd(width)
turtle.left(90)
turtle.fd(height)
turtle.left(90)
turtle.left(angle)
turtle.fd(hypo)
turtle.hideturtle()
