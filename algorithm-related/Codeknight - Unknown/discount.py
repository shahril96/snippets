
from decimal import Decimal

input_data = raw_input().split(' ')
val = float(input_data[0])
discount = float(input_data[1])
calc = Decimal(val) - Decimal(val * discount // 100)
print(str(calc))