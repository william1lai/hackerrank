import math
import sys

msg = raw_input()
side = int(math.ceil(len(msg)**0.5))

for i in range(side):
    for j in range(0, len(msg) - i, side):
        sys.stdout.write(msg[i + j])
    sys.stdout.write(' ')