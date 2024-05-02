from matplotlib.pyplot import plot, show, figure
from math import sin, cos, pi
import numpy as np
from mpl_toolkits.mplot3d import Axes3D


def Display3D(DATA, T):
    # % scaling factor
    s = T[3][3]

    # % draw the X, Y, Z axis
    X = np.array([1, 0, 0, 1]).transpose()
    Y = np.array([0, 1, 0, 1]).transpose()
    Z = np.array([0, 0, 1, 1]).transpose()
    O = np.array([0, 0, 0, 1]).transpose()

    DATA = DATA @ T

    T0 = T
    T0[0][3] = 0
    T0[1][3] = 0
    T0[2][3] = 0

    # % transform
    X0 = T0 @ X
    Y0 = T0 @ Y
    Z0 = T0 @ Z
    Origin = T0 @ O

    # % display is the y-z plane
    plot([-2, 2], [-2, 2], 'wx')

    # % Project onto the YZ axis

    Tx = s * np.array([[0, 1, 0, 0]])
    Ty = s * np.array([[0, 0, 1, 0]])

    plot(Tx * [Origin, X0], Ty * [Origin, X0], 'r')
    plot(Tx * [Origin, Y0], Ty * [Origin, Y0], 'r')
    plot(Tx * [Origin, Z0], Ty * [Origin, Z0], 'm')

    # % display the data
    plot(DATA * Tx, DATA * Ty, 'b')
    show()


# % Translation

X = np.array([0, 0, 0, 0, 0, 0, 0, 0]).transpose()
Y = np.array([-0.5, 0.5, 0.5, 1, 0, -1, -0.5, -0.5]).transpose()
Z = np.array([0, 0, 0.5, 0.5, 1, 0.5, 0.5, 0]).transpose()
X1 = np.array([x + 1 for x in X])

ARROW = np.array([X, Y, Z, X1]).transpose()

c = cos(-25 * pi / 180)
s = sin(-25 * pi / 180)
Ry = np.array([[c, 0, -s, 0], [0, 1, 0, 0], [s, 0, c, 0], [0, 0, 0, 1]])

c = cos(-45 * pi / 180)
s = sin(-45 * pi / 180)
Rz = np.array([[c, -s, 0, 0], [s, c, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]])

Tdisp = Ry * Rz

T = np.eye(4, 4)
for i in range(1, 181):
    dx = sin(i * pi / 90)
    T[0][3] = dx
    Display3D(np.matmul(ARROW, T), Tdisp)

for i in range(1, 181):
    dy = sin(i * pi / 90)
    T[1][3] = dy
    Display3D(np.matmul(ARROW, T), Tdisp)

for i in range(1, 181):
    dz = sin(i * pi / 90)
    T[2][3] = dz
    Display3D(np.matmul(ARROW, T), Tdisp)
