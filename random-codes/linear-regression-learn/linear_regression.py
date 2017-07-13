
import matplotlib.pyplot as plt
import math


LEARNING_RATE = 0.05


def gradient_descent(x, y, iteration):

    theta0, theta1 = 0.0, 0.0
    m = len(x)  # either x or y is ok

    '''
    PRE-PROCESSING THE DATA (FEATURE SCALING)
    '''

    xavg = sum(x) / m
    xstd_deviation = math.sqrt(sum([(e-xavg)**2 for e in x]) / m)

    for i in range(m):
        x[i] = (x[i] - xavg) / xstd_deviation

    '''
    CALCULATION OF THETA VALUES USING GRADIENT DESCENT ALGORITHM
    '''

    for i in range(iteration):

        tmp_theta0 = sum([theta0+theta1*x[j]-y[j] for j in range(m)]) / m
        tmp_theta1 = sum([(theta0+theta1*x[j]-y[j])*x[j] for j in range(m)]) / m

        theta0 -= LEARNING_RATE * tmp_theta0
        theta1 -= LEARNING_RATE * tmp_theta1

        print((theta0, theta1))

    return (theta0, theta1)


with open("./data.txt", "r") as fi:

    '''
    TAKING CSV DATA
    '''

    data = fi.read().split("\n")

    label1, label2 = data[0].split(",")
    x, y = [], []

    for i in range(1, len(data)):
        if data[i]:
            ex, ey = data[i].split(",")
            x.append(float(ex))
            y.append(float(ey))

    '''
    GET THETA VALUES
    '''

    theta0, theta1 = gradient_descent(x, y, 100)

    '''
    PLOT THE DATA & OPTIMUM LINE USING MATPLOTLIB
    '''

    #  line data
    min_l = int(math.floor(min(x)))
    max_l = int(math.ceil(max(x)))
    min_list = []
    line = []

    while min_l <= max_l:
        line.append(theta0 + theta1*min_l)
        min_list.append(min_l)
        min_l += 0.1

    plt.plot(x, y, "ro", min_list, line)
    plt.xlabel(label1)
    plt.ylabel(label2)
    plt.show()
