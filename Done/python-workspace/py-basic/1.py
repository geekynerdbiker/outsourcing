"""
Prob 1
"""

price = [10.5, 2.50, 35.50, 42.00]
discount = [0, 0, 0.15, 0.10]
units = [232, 1100, 569, 348]
total = 0

for i in range(len(price)):
    total = total + (price[i] * (1 - discount[i]) * units[i])
print("The total sales is: $" + str(round(total, 2)))

