import numpy as np
from numpy import linalg as LA


def problem2():
    a = np.random.randn(1000, 1000)
    Q = np.dot(a, a.transpose())
    b = np.random.randn(1000, 1)

    return a, Q, b


def gradient_descent(x_data, y_data):
    a = 0
    b = 0
    lr = 0.05

    y_pred = a * x_data + b
    error = y_data - y_pred

    a_diff = -(1 / len(x_data)) * sum(x_data * (error))
    b_diff = -(1 / len(x_data)) * sum(y_data - y_pred)

    a = a - lr * a_diff
    b = b - lr * b_diff

    print(a)
    print(b)


def is_pos_def(x):
    return np.all(np.linalg.eigvals(x) > 0)


def steepest_descent(A, b, x):
    if (is_pos_def(A) == False) | (A != A.T).any():
        raise ValueError('Matrix A needs to be symmetric positive definite (SPD)')
    r = b - A @ x
    k = 0
    while LA.norm(r) > 1e-10:
        p = r
        q = A @ p
        alpha = (p @ r) / (p @ q)
        x = x + alpha * p
        r = r - alpha * q
        k = + 1

    return x
