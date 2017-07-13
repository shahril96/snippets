
from __future__ import division
from decimal import Decimal


def triangle(a):
    calc = (Decimal(3).sqrt() / Decimal(4)) * (Decimal(a)**2)
    return calc

b, bl, tl, t, tr, br = map(Decimal, raw_input().split(' '))
hexagon = triangle(bl+tl+t) - triangle(bl) - triangle(t) - triangle(br)
print(int(hexagon / Decimal(0.433012701892)))