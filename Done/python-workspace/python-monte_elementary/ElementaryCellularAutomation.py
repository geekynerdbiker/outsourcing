import numpy as np
import matplotlib.pyplot as plt

U = np.array([[4], [2], [1]])


def Step(Rule, X):
    Y = np.vstack((np.roll(X, 1), X, np.roll(X, -1))).astype(np.int8)
    Z = np.sum(Y * U, axis=0).astype(np.int8)

    return Rule[7 - Z]


def generate(Rule, Size=100, Steps=100):
    RuleNext = np.array([int(_) for _ in np.binary_repr(Rule, 8)], dtype=np.int8)
    X = np.zeros((Steps, Size), dtype=np.int8)
    X[0, :] = np.random.rand(Size) < .5

    for i in range(Steps - 1):
        X[i + 1, :] = Step(RuleNext, X[i, :])

    return X


Figure, Axes = plt.subplots(3, 3, figsize=(8, 8))
Rules = [30, 40, 57, 73, 90, 110]

for ax, rule in zip(Axes.flat, Rules):
    x = generate(rule)
    ax.imshow(x, interpolation='none', cmap=plt.cm.binary)
    ax.set_axis_off()
    ax.set_title(str(rule))
