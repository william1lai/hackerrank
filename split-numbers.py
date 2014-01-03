import re

N = input()
for i in range(N):
    num = raw_input()
    hi = re.split("[ -]", num)
    print "CountryCode=" + hi[0] + ",LocalAreaCode=" + hi[1] + ",Number=" + hi[2]