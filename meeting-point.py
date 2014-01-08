#!/usr/bin/py
# Head ends her
def meetingPoint(x,y):
    bx = 1.0*sum(x)/len(x)
    by = 1.0*sum(y)/len(y)
    mdist = -1
    mind = -1
    for i in range(len(x)):
        ans = (x[i]-bx)**2 + (y[i]-by)**2
        if i == 0 or ans < mdist:
            mdist = ans
            mind = i
    summation = 0
    for j in range(len(x)):
        summation = summation + max(abs(x[mind]-x[j]), abs(y[mind]-y[j]))
    return summation
        

# Tail starts here
if __name__ == '__main__':
    a = input()
    x=[0]*a
    y=[0]*a
    for i in range(0,a):
        b = map(int, raw_input().strip().split(" "))
        x[i]=b[0]
        y[i]=b[1]
    print meetingPoint(x,y)