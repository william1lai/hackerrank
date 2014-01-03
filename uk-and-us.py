import re

N = input()
text = []
for i in range(N):
    text.extend(raw_input().split(' '))
T = input()
for i in range(T):
    w = raw_input()
    w2 = re.sub("ze$", "se", w)
    count = 0
    for s in text:
        if w == s or w2 == s:
            count = count + 1
    print count