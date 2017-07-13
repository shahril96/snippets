
"""
 a 5 lines solution for IWGBS - 0110SS problem
 after finding it properties, we can develop O(n) solution easily
"""

N = int(raw_input())
i, o = 1, 0
while(N > 1):
    i, o, N = i+o, i, N-1
print(2*i + o)