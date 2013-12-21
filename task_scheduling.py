ntasks = input()
jobs = []
for i in range(ntasks):
    a,b = raw_input().split()
    jobs.append((int(a),int(b)))

for i in range(1, ntasks + 1):
    consider = sorted(jobs[0:i])
    overshoot = 0
    time = 0
    for j in range(0, i):
        time = time + consider[j][1]
        if time > consider[j][0] and time - consider[j][0] > overshoot:
            overshoot = time - consider[j][0]
    print overshoot