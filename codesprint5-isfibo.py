fibs = set()
fibs.add(1)
last = 1
cur = 1
while (cur <= 10000000000):
    temp = cur
    cur = last + cur
    last = temp
    fibs.add(cur)

N = input()
for i in range(N):
    x = input()
    if x in fibs:
        print "IsFibo"
    else:
        print "IsNotFibo"