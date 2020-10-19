def foo(n):
    if n<1:
        print('')
    else:
        print('*',end='')
        foo(n-1)


def reverseNum(n):
    if n//10==0:
        print(n)
    else:
        print(n%10,end='')
        reverseNum(n//10)

def maxValue(vals):
    if len(vals)>1:
        if vals[0]<=vals[1]:
            vals.remove(vals[0])
            maxValue(vals)
        else:
            vals.remove(vals[1])
            maxValue(vals)
    else:
        return print(vals[0])
