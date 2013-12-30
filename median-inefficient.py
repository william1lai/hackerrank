#!/bin/python
def printMedian(nums):
    length = len(nums)
    if length == 0:
        print 0
    elif length % 2 == 0:
        ans = (nums[length/2] + nums[length/2 - 1])
        if ans % 2 == 0:
            print ans / 2
        else:
            print ans / 2.0
    else:
        print nums[length/2]

def median(s,x):
    nums = []
    for i in range(len(s)):
        action = s[i]
        n = x[i]
        if action == 'r':
            if len(nums) <= 1:
                print "Wrong!"
            else:
                if n in nums:
                    nums.remove(n)
                    printMedian(nums)
                else:
                    print "Wrong!"
        elif action == 'a':
            nums.append(n)
            nums.sort()
            printMedian(nums)
            
N = input()
s = []
x = []
for i in range(0, N):
   tmp = raw_input().strip().split(' ')
   a, b = [xx for xx in tmp]
   s.append(a)
   x.append(int(b))
median(s,x)