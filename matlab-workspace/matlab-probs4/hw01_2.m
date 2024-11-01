clear; clc;

f = inline('x.^3 + x - 1')
x = 1:0.1:10
y = f(x)

print('hw01_2','-dpng')
