N = input()
for i in range(N):
    length = input()
    nums = sorted([int(x) for x in raw_input().split()])
    
    ways = 1
    index = 0
    avail = 0
    for j in range(length):
        count = 0
        for k in range(j, length):
            if nums[k] <= j:
                count = count + 1
                avail = avail + 1
            else:
                avail = k - 1
                break
        if count == 0:
            ways = 0
            break
        else:
            ways = ways*count
    
    print ways % 1000000007

