valids = []
for i in range(1, 100000):
    s = ""
    j = i
    while j > 0:
        hi = j % 2
        j = j / 2
        if hi:
            s = "9" + s
        else:
            s = "0" + s
    valids.append(int(s))

N = input()
for i in range(N):
    z = input()
    for x in valids:
        if x % z == 0:
            print x
            break