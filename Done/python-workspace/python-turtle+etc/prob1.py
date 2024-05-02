import turtle as t


def fx(x):
    return x ** 2 + 3


t.home()
t.shape("turtle")

for x in range(101):
    t.goto(x, fx(x))
