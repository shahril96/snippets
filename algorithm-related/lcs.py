
# recursive method
def lcs(a, b):

    if(len(a) <= 0 or len(b) <= 0):
        return 0

    elif(a[-1] == b[-1]):
        return lcs(a[:-1], b[:-1]) + 1

    else:
        return max(lcs(a[:-1], b), lcs(a, b[:-1]))


def lcs_dp(a, b):

    # initilize list of matrix with len(a) * len(b) and zero as its element
    word = [[0 for i in range(len(b) + 1)] for i in range(len(a) + 1)]

    for x in range(1, len(a) + 1):
        for y in range(1, len(b) + 1):

            if(a[x-1] == b[y-1]):
                word[x][y] = word[x-1][y-1] + 1

            else:
                word[x][y] = max(word[x-1][y], word[x][y-1])

    return word[len(a)][len(b)]


print lcs('kuhkuh3', 'kuh')
print lcs_dp("aabdc", "kaacl")
