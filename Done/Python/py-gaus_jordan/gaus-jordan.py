import numpy as np


def solve(matrix):
    matrix = np.array(matrix)
    m, n = A.shape
    if m != n:
        raise Exception("The input matrix should be a square")

    # create an Identity matrix of size mxm
    I = np.eye(m)

    # Augment matrix A
    aug_A = np.c_[A, I]

    # Gaussian Elimination to generate an upper triangular matrix
    j = 0
    for i in range(m - 1):
        pivot = aug_A[i][j]
        if pivot == 0:

            found = False
            for k in range(i + 1, m):
                if aug_A[k][j] != 0:
                    temp = aug_A[k].copy()
                    aug_A[k] = aug_A[i].copy()
                    aug_A[i] = temp.copy()
                    found = True
                    break
            if not found:
                raise Exception("The matrix is singular and hence cannot be inverted")
            else:
                pivot = aug_A[i][j]
        for k in range(i + 1, m):
            target = aug_A[k][j]
            multiplier = target / pivot
            aug_A[k] = aug_A[k] - multiplier * aug_A[i]
        j += 1

    # Generate 0s above the pivot and create a diagonal matrix
    j = m - 1
    for i in range(m - 1, 0, -1):
        pivot = aug_A[i][j]
        for k in range(i - 1, -1, -1):
            target = aug_A[k][j]
            multiplier = target / pivot
            aug_A[k] = aug_A[k] - multiplier * aug_A[i]
        j -= 1

    for i in range(m):
        aug_A[i] /= aug_A[i][i]

    return aug_A[:, m:]


m = 3

# Use this line before submit!
# A = np.random.randint(0, 10, size=(m,m))

# This line is for test case.
A = np.array([[2, 3, -1], [4, 4, -3], [-2, 3, -1]])

A_inv = solve(A)
m = A_inv.shape[0]

# Generate Identity matrix of size mxm
I_excepted = np.eye(m)

# To account for floating point imprecision
I_actual = np.round(np.dot(A, A_inv))

assert np.all(I_excepted == I_actual)
print("Original: ")
print(A)
print("\nInverse of A: ")
print(A_inv)
