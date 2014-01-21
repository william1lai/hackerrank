player = input()
pikachu = [int(x) for x in raw_input().split(' ')]
nhand = pikachu[0]
ntable = pikachu[1]

ri = raw_input()[:-1]
hand = sorted([int(x) for x in ri.split(' ')])

if ntable > 0:
    table = sorted([int(x) for x in raw_input().split(' ')])
    
if ntable == 0:
    print hand[0], 0
else:
    play = hand[0]
    total = 0
    capture = []
    for i in range(ntable):
        if total + table[i] >= play:
            break
        else:
            total = total + table[i]
            capture.append(str(table[i]))
    print play, len(capture)
    print " ".join(capture)