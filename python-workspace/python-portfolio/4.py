from numpy import zeros, random
import matplotlib.pyplot as plt

knockout_down = 800
knockout_up = 1200

S_init = 1000
T = 1.5
tstep = 0.001
sigma = 0.30
mu = 1

plt.figure()

Steps = round(T / tstep)
S = zeros([int(Steps)], dtype=float)
x = range(0, int(Steps), 1)

r, g, b = tuple(random.choice(range(256), size=3))
color = (r / 255., g / 255., b / 255.)

S[0] = S_init
for i in x[:-1]:
    if i <= 800:
        S[i] = 0
    elif i > 800 and i <= 1000:
        S[i] = S_init - i
    elif i > 1000 and i <= 1200:
        S[i] = i - S_init
    elif i > 1200:
        S[i + 1] = 0
line = plt.scatter(x, S)
plt.axis([500, 1500, 0, 300])
plt.setp(line, color='r', linewidth=2.0)
plt.show()
