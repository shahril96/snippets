
import random

m = 3  # how many data sets to generate

with open("data.txt", "w") as fo:

    fo.write("House Age (Year), Price (RM 100k)\n")

    # initial value
    age, price = 3, 2000

    for i in range(m):
        fo.write("%f, %f\n" % (age, price))
        age = max(0, age + random.uniform(0, 5))
        price = max(0, price - random.uniform(10, 50))
