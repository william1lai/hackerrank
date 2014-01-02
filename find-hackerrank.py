import re

N = input()
for i in range(N):
    s = raw_input()
    start = False
    end = False
    if re.search("^hackerrank", s):
        start = True
    if re.search("hackerrank$", s):
        end = True
    if start and end:
        print 0
    elif start:
        print 1
    elif end:
        print 2
    else:
        print -1