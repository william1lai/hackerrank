def ways(width):
    perm = [ 1 ]
    for i in range(1, width + 1):
        total = 0
        if i > 3:
            total = total + perm[i-4]
        if i > 2:
            total = total + perm[i-3]
        if i > 1:
            total = total + perm[i-2]
        total = total + perm[i-1]
        perm.append(total)
    return perm

N = input()
for i in range(N):
    data = [int(x) for x in raw_input().split()]
    height = data[0]
    width = data[1]
    
    dp = [ 0, 1 ]
    for j in range(2, width+1):
        perm = ways(j)    
        overcount = perm[-1]**height
        sub = 0
        for i in range(1, j):
            sub = sub + dp[i]*(perm[j-i]**height)
        dp.append((overcount - sub) % 1000000007)
    print dp[-1]
            