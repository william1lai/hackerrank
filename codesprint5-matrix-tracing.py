mo = 1000000007

def power(a, b, mod):
    x = 1
    y = a    
    while b > 0:
        if b % 2 == 1:
            x = x*y
            if x > mod:
                x = x % mod
        y = y*y
        if y > mod:
            y = y % mod
        b = b / 2
    return x

def inverseEuler(n, mod):
    return power(n, mod - 2, mod)

def C(n, r, mod):
    f = [1 for x in range(n+1)]
    for i in range(2, n+1):
        f[i] = (f[i-1]*i) % mod
    return (f[n]*((inverseEuler(f[r], mod) * inverseEuler(f[n-r], mod)) % mod)) % mod

N = input()
for i in range(N):
    pikachu = [int(x) for x in raw_input().split(' ')]
    m = pikachu[0] - 1
    n = pikachu[1] - 1
    poss = m + n
    if m < n:
        print C(poss, m, mo)
    else:
        print C(poss, n, mo)
        
