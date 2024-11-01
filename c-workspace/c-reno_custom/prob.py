import numpy as np
import math

## Q1
data = np.array([
    1.000, 0.994, 0.990, 0.985, 0.979, 0.977,
    0.972, 0.969, 0.967, 0.960, 0.956, 0.952,
])


def half_life_model(t, a, b):
    return a * np.exp(-b * t)


def optimize(params):
    a, b = params
    sum = 0
    for d in data:
        sum += d - half_life_model(d, a, b)
    return sum ** 2


result = optimize([1.0, 0.01])
print("반감기:", result)


## Q2
def func(eta, y):
    return math.exp(-eta * (y - 1) / (y * math.log(eta)))


eta = 0.35
y = 5 / 3
T2_over_T1 = func(eta, y)
print("T2 / T1 = {}".format(T2_over_T1))
