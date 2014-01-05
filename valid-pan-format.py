import re

N = input()
for i in range(N):
    s = raw_input()
    if re.search("^[A-Z]{5}[0-9]{4}[A-Z]$", s):
        print "YES"
    else:
        print "NO"