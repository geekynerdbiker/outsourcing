import matplotlib.pyplot as plt
import scipy.optimize as opt
import numpy as np
import warnings

warnings.filterwarnings(action='ignore')


# F = @(x,xdata)(x(1)*exp(-x(2)*xdata) + x(3)*exp(-x(4)*xdata))
def func(x, x1, x2, x3, x4):
    return x1 * np.exp(-(x2*x)) + x3 * np.exp(-(x4*x))


xdata = []
ydata = []

D = input("Dose를 입력하세요:")

for i in range(1, 5):
    x = input(i.__str__() + "번째 채혈시간을 입력하세요:")
    xdata.append(float(x))
for i in range(1, 5):
    y = input(i.__str__() + "번째 엑셀 계산값을 입력하세요:")
    ydata.append(float(y))

plt.plot(xdata, ydata, 'ko')
plt.show()

# 플로팅 초기
x0 = [ydata[0], 0.01, ydata[1], 0.1]

# 커브 피팅 시행
popt, pcov = opt.curve_fit(func, xdata, ydata, x0)

# 커브그래프 작성
plt.plot(xdata, ydata, 'ko', label='Data')
xx = np.linspace(xdata[0], xdata[3])
plt.plot(xx, func(xx, *popt), label='Fitted exponential')
plt.legend()
plt.title('Data and Fitted Curve')

plt.show()

x = popt
GFR = float(D)*x[1]*x[3]/(x[0]*x[3]+x[2]*x[1])

print("GFR = " + str(GFR))
