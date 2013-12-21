import numpy

ncases = input()

for i in range(ncases):
    N = input()
    stock = [int(x) for x in raw_input().split()]
    profit = 0
    biggest = stock[N-1]
    for j in range(N-2, -1, -1):
        if stock[j] < biggest:
            profit = profit + biggest - stock[j]
        else:
            biggest = stock[j]
    print profit
            