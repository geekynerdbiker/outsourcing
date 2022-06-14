import numpy as np
import matplotlib.pyplot as plt

np.random.seed(0)

# 3-1
mu1, sigma1 = 0.0, 1.0
mu2, sigma2 = 0.0, 1.5
mu3, sigma3 = 0.0, 2.0

x = np.linspace(-8, 8, 1000)
y1 = (1 / np.sqrt(2 * np.pi * sigma1 ** 2)) * np.exp(-(x - mu1) ** 2 / (2 * sigma1 ** 2))
y2 = (1 / np.sqrt(2 * np.pi * sigma2 ** 2)) * np.exp(-(x - mu2) ** 2 / (2 * sigma2 ** 2))
y3 = (1 / np.sqrt(2 * np.pi * sigma3 ** 2)) * np.exp(-(x - mu3) ** 2 / (2 * sigma3 ** 2))

plt.axis([-10.0, 10.0, 0.0, 0.5])
plt.plot(x, y1, alpha=0.7, label=r'Normal distributuin of mean 0, standard devitation 1')
plt.plot(x, y2, alpha=0.7, label=r'Normal distributuin of mean 0, standard devitation 1.5')
plt.plot(x, y3, alpha=0.7, label=r'Normal distributuin of mean 0, standard devitation 2')
plt.legend()
plt.show()


# 3-2
mu1, sigma1 = 0.0, 1.0
mu2, sigma2 = 1.0, 1.5
mu3, sigma3 = 2.0, 2.0

x = np.linspace(-8, 8, 1000)
y1 = (1 / np.sqrt(2 * np.pi * sigma1 ** 2)) * np.exp(-(x - mu1) ** 2 / (2 * sigma1 ** 2))
y2 = (1 / np.sqrt(2 * np.pi * sigma2 ** 2)) * np.exp(-(x - mu2) ** 2 / (2 * sigma2 ** 2))
y3 = (1 / np.sqrt(2 * np.pi * sigma3 ** 2)) * np.exp(-(x - mu3) ** 2 / (2 * sigma3 ** 2))

plt.axis([-10.0, 10.0, 0.0, 0.5])
plt.plot(x, y1, alpha=0.7, label=r'Normal distributuin of mean 0, standard devitation 1')
plt.plot(x, y2, alpha=0.7, label=r'Normal distributuin of mean 1, standard devitation 1.5')
plt.plot(x, y3, alpha=0.7, label=r'Normal distributuin of mean 2, standard devitation 2')
plt.legend()
plt.show()
