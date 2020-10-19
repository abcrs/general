import turtle
import random

def tree(t, trunkLength):
    right=random.randint(0,30)+15
    left=right*2
    branch1=random.randint(0,6)+12
    branch2=random.randint(0,6)+12
    if trunkLength<5:
        return
    else:
        t.forward(trunkLength)
        t.right(right)
        tree(t,trunkLength-branch1)
        t.left(left)
        tree(t,trunkLength-branch2)
        t.right(right)
        t.backward(trunkLength)


def main():
    tur=turtle.getturtle()
    tur.left(90)
    tree(tur,100)

if __name__=='__main__':
    main()
