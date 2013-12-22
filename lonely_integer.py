#!/usr/bin/py
# Head ends here
def lonelyinteger(b):
    once = set()
    twice = set()
    for x in b:
        if x in once:
            twice.add(x)
        else:
            once.add(x)
    answer = (once - twice).pop()
    return answer
# Tail starts here
if __name__ == '__main__':
    a = input()
    b = map(int, raw_input().strip().split(" "))
    print lonelyinteger(b)