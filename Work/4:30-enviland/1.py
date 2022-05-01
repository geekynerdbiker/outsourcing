from numpy.random import standard_normal
from numpy import zeros, sqrt, random
import matplotlib.pyplot as plt

S_init = 70000
T = 3
tstep = 0.02
sigma = 0.2
mu = 0.15
NumSimulation = 10

plt.figure()

Steps = round(T / tstep)
S = zeros([NumSimulation, int(Steps)], dtype=float)
x = range(0, int(Steps), 1)

# 1-1
for j in range(0, NumSimulation, 1):
    r, g, b = tuple(random.choice(range(256), size=3))
    color = (r / 255., g / 255., b / 255.)

    S[j, 0] = S_init
    for i in x[:-1]:
        S[j, i + 1] = S[j, i] + S[j, i] * (mu - 0.15 * pow(sigma, 2)) * tstep + sigma * S[j, i] * sqrt(
            tstep) * standard_normal()
plt.plot(x, S[0], linewidth=0.5, color=color)
plt.show()

# 1-2
for j in range(0, NumSimulation, 1):
    r, g, b = tuple(random.choice(range(256), size=3))
    color = (r / 255., g / 255., b / 255.)

    S[j, 0] = S_init
    for i in x[:-1]:
        S[j, i + 1] = S[j, i] + S[j, i] * (mu - 0.15 * pow(sigma, 2)) * tstep + sigma * S[j, i] * sqrt(
            tstep) * standard_normal()
    plt.plot(x, S[j], linewidth=0.5, color=color)
plt.show()
