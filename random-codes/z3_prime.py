
'''
Using Z3 to check if the number is prime
Original reference: https://stackoverflow.com/a/35653749/1768052
'''

from z3 import *

def isPrime(x):
    y, z = Ints("y z")
    return And(x > 1, Not(Exists([y, z], And(y < x, z < x, y > 1, z > 1, x == y*z))))

s = Solver()

x = Int('x')
s.add(isPrime(x))

while s.check() == sat:
    ans = s.model()[x]
    print(ans)
    s.add(x != ans)