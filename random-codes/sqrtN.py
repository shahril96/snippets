
from decimal import Decimal as D

search = None


def f(N):

    """

    sqrt(search) = N
    search       = N^2
    0            = N^2 - search

    task : find N value which will make above equation true

    """

    return D(N)**2 - D(search)


def derivative_numerical(f, x):
    h = D("1e-20")
    return (f(x+h)-f(x-h)) / (h*2)


def newton_method(iteration):

    root = D(1.0)   # set initial value

    for i in range(iteration):
        print("i = " + str(i+1) + ", N = " + str(root))
        newroot = root - f(root) / derivative_numerical(f, root)
        if newroot == root:
            break
        root = newroot


def main():
    global search
    search = input("Enter any number to find its square root : ")
    newton_method(search)


if __name__ == '__main__':
    main()
