clc; clear all;

%%%%%%%%%%%%%%% Problem 1 %%%%%%%%%%%%%%%
func = @(x) -12 -21*x + 18*x^2 -2.75*x^3;
xl=-1; xu=0; error=0.01; iter = 10;

% (a)
syms x;
y=-12 -21*x + 18*x^2 -2.75*x^3;
solve(y==0, x)
figure(1)
fplot(y)

print -dpng 'p1.png'

% (b)
bisection(func, xl, xu, error, iter);

% (c)
false_loc(func, xl, xu, error, iter);


%%%%%%%%%%%%%%% Problem 2 %%%%%%%%%%%%%%%
syms x;
func = x^3 -6*x^2+11*x-6.1;
xi=3.5; xl=2.5; xu=3.5; delta=0.01; iter=4;

% (a)
y=x^3 -6*x^2+11*x-6.1;
solve(y==0,x)
figure(2)
fplot(func)

print -dpng 'p2.png'

% (b)
NR(func, diff(func), xi, error, iter);

% (c)
func = @(x) x^3 -6*x^2+11*x-6.1;
SC(func, xl, xu, error, iter);

% (d)
SC(func, xi, delta, error, iter);

% (e)

%%%%%%%%%%%%%%% Problem 3 %%%%%%%%%%%%%%%
syms x1 x2;

y1 = 4*x1 - 8*x2;
y2 = x1 + 6*x2;

X = solve(y1==-24, x1, x2);
4*X.x1 - 8*X.x2 == -24

X = solve(y2==34, x1, x2);
X.x1 + 6*X.x2 == 34


%%%%%%%%%%%%%%% Problem 4 %%%%%%%%%%%%%%%
% (c)
matrix = [8,2,1; 3,7,1; 2,3,9;]
LUNaive(matrix)
