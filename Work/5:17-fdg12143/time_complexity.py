import math
import random


def problem02():
    def f(n):
        return 2 * n ** 2 + 3 * n + 2

    def g(n):
        return int(math.pow(n, 2))

    c = 1
    n0 = 1
    return f, g, c, n0


def problem03():
    def f(n):
        return 2 * n ** 3 + 3 * n ** 2 + 3 * n + 3

    def g(n):
        return n ** 3

    c = 1
    n0 = 1
    return f, g, c, n0


def problem04():
    def f(n):
        k = math.ceil(math.sqrt(n))
        return int(2 ** k) - 1 + 2 * k + 3 * (n + 1)

    def g(n):
        k = math.ceil(math.sqrt(n))
        return int(2 ** k)

    c = random.random() % 10 + 1
    n0 = random.random() % 10 + 1

    return f, g, c, n0


def problem05():
    def f(n):
        k = math.ceil(math.sqrt(n))
        return 2 + 2 * n + n * int(3 ** n) * 3 * int(2 ** k) - 1 + 2 * k + 3 * (n + 1)

    def g(n):
        k = math.ceil(math.sqrt(n))
        return n * int(3 ** n) * 3 * int(2 ** k) - 1 + 2 * k + 3 * (n + 1)

    c = int(random.random() % 10 + 1)
    n0 = int(random.random() % 10 + 1)

    return f, g, c, n0
