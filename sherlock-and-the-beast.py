import sys

N = input()
for i in range(N):
    num = input()
    fivesets = 0
    threesets = 0
    while num > 0 and num % 3 != 0:
        threesets = threesets + 1
        num = num - 5
    if num >= 0 and num % 3 == 0:
        fivesets = num / 3
        for j in range(fivesets):
            sys.stdout.write("555")
        for j in range(threesets):
            sys.stdout.write("33333")
        print
    else:
        print -1