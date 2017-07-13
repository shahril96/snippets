
input_data, findc = raw_input().split(' ')

n = 0

for c in input_data:
    if c == findc:
        n += 1

print(n)