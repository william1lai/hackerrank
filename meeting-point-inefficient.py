#!/usr/bin/py
# Head ends here
def meetingPoint(x,y):
    
    answer = -1
    for i in range(len(x)):
        summation = 0
        for j in range(len(x)):
            summation = summation + max(abs(x[j]-x[i]), abs(y[j]-y[i]))
        if i == 0 or summation < answer:
            answer = summation            
    return answer

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