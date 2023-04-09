"""
Prob 3
"""
import math

numbers = [3.5, 3.7, 4.5, 2.7, 5.8, 9.9]
total = 0

mean = sum(numbers) / len(numbers)
for number in numbers:
    total = total + (number - mean) ** 2
sd = math.sqrt(total / len(numbers))
print("Mean is: " + str(round(mean, 2)) + " and standard deviation is: " + str(round(sd, 2)))
