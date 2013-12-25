N = input()
for i in range(N):
    s = raw_input()
    if len(s) % 2 == 1:
        print -1
    else:
        s1 = sorted(s[:(len(s)+1)/2])
        s2 = sorted(s[len(s1):])
        count = len(s2)
        index1 = 0
        index2 = 0
        
        while index1 < len(s1) and index2 < len(s2):
            if s1[index1] == s2[index2]:
                count = count - 1
                index1 = index1 + 1
                index2 = index2 + 1
            elif s1[index1] > s2[index2]:
                index2 = index2 + 1
            else:
                index1 = index1 + 1
        
        print count