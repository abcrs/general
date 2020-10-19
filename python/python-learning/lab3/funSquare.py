import turtle
def Drawsquare(sidelength):
    turtle.fd(sidelength)
    turtle.left(90)
    turtle.fd(sidelength)
    turtle.left(90)
    turtle.fd(sidelength)
    turtle.left(90)
    turtle.fd(sidelength)
    turtle.left(90)
def main():
    runs=turtle.numinput("","Please enter the number of squares you'd like to draw: ")
    rotation=360/runs
    while runs>0:
        Drawsquare(100)
        turtle.left(rotation)
        runs=runs-1

if __name__=='__main__':
  main()
