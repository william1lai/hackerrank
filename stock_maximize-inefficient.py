import numpy

ncases = input()

for i in range(ncases):
    N = input()
    stock = [int(x) for x in raw_input().split()]
    olddp = []
    newdp = []
    for j in range(N):
        if j == 0:
            newdp.append(0)
            newdp.append(-stock[0])
        else:
            for jj in range(j+2): #look at previous day's earnings
                maxi = -99999999999
                for k in range(0, j+1):
                    if jj <= k and olddp[k] + (k-jj)*stock[j] > maxi:
                        maxi = olddp[k] + (k-jj)*stock[j]
                    elif jj == k+1 and olddp[k] - stock[j] > maxi:
                        maxi = olddp[k] - stock[j]

                newdp.append(maxi)
        
        olddp = list(newdp)
        newdp = []
    
    print int(olddp[0])
