ncases = input()

for i in range(ncases):
    desired = input()
    nflavs = input()
    costs = [int(x) for x in raw_input().split(" ")]
    done = False
    
    for j in range(nflavs):
        for k in range(j + 1, nflavs):
            if costs[j] + costs[k] == desired:
                done = True
                break
        if done:
            break
    print j + 1, k + 1
