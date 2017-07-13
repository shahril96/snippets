
from math import sqrt

def isPrime(term):

    # if divisible by 2 or 3, sure not prime
    if term % 2 == 0: return False
    if term % 3 == 0: return False

    # loop odd numbers only
    # loop starts from 5
    for j in range(5, int(sqrt(term))+1, 2): 
        if term % j == 0:
            return False 
    
    return True

# this algo is slow. may not be efficient
primes = [2, 3]
i = 5
lim = 10001

while len(primes) <= lim:

    if isPrime(i) is True:
        primes.append(i)
    
    i += 1

print primes[lim-1]