import math

N = input()
for i in range(N):
    pikachu = [int(x) for x in raw_input().split(' ')]
    m = pikachu[0] - 1
    n = pikachu[1] - 1
    poss = m + n
    ans = math.factorial(poss) / (math.factorial(m) * (math.factorial(n)))
    print ans