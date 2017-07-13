
def bin_search(lis, x):

    lo, hi = 0, len(lis)-1

    while lo < hi:
        mid = int((hi+lo)/2)
        if lis[mid] >= x:
            hi = mid
        else:
            lo = mid+1

    return hi

_ = int(input())
lis = []

for x in range(_):
    if len(lis) == 0 or lis[len(lis)-1] < x:
        lis.append(x)
    else:
        s = bin_search(lis, x)
        lis[s] = x

print(len(lis))
