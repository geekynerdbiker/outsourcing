import numpy as np
from scipy import io
from PIL import Image
import os


def omp(A, y, K):
    m, n = A.shape
    X = np.zeros((n, n))

    for i in range(n):
        residual = y[:, i]
        x = np.zeros(n)
        index_set = []

        x_selected = []
        for _ in range(int(K[0, i])):
            projections = A.T @ residual
            best_index = np.argmax(np.abs(projections))

            if best_index in index_set:
                break

            index_set.append(best_index)

            A_selected = A[:, index_set]
            x_selected, _, _, _ = np.linalg.lstsq(A_selected, y[:, i], rcond=None)
            residual = y[:, i] - A_selected @ x_selected

        for j, index in enumerate(index_set):
            x[index] = x_selected[j].real

        X[:, i] = x

    return X


def run_file(filename):
    mat = io.loadmat(filename)
    A = mat['A']
    y = mat['y']
    K = mat['s']

    x_hat = omp(A, y, K)
    img = Image.fromarray(np.abs(x_hat)).convert('L')
    img.save('result/' + filename.split('.')[0] + '_result.png')


if __name__ == '__main__':
    for file in os.listdir(os.getcwd()):
        if '.mat' in file:
            run_file(file)
