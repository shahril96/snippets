
import sys

input_data = raw_input().split(' ')

for word in input_data:
    l = len(word)
    if len(word) >= 7:
        sys.stdout.write(word[0] + word[1] + str(l-4) + word[l-1] + word[l-2])
    else:
        sys.stdout.write(word)

    sys.stdout.write(' ')