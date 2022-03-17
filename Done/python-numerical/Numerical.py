import math


class Numerical:
    def __init__(self, types="cubic", a=0.0, b=0.0, c=0.0, d=0.0, x1=0.0, x2=0.0, tol=0.0):
        self.types = types
        self.a = a
        self.b = b
        self.c = c
        self.d = d

        self.x1 = x1
        self.x2 = x2
        self.tol = tol

        self.iteration = 0
        self.x = 0.0

        self.print_function()
        self.binary_search(self.x1, self.x2, self.tol)
        self.print_result()
        print()

    def f(self, k):
        if self.types == "exp":
            return self.a * math.exp(k) + self.b
        elif self.types == "cubic":
            return self.a * pow(k, 3) + self.b * pow(k, 2) + self.c * k + self.d
        elif self.types == "log":
            return self.a * math.log(k) + self.b

    def binary_search(self, low, high, tol):
        while low <= high:
            self.x = (low + high) / 2
            while abs(self.f(self.x)) > tol:
                if self.f(low) * self.f(self.x) > 0:
                    low = self.x
                else:
                    high = self.x

                self.iteration += 1
                self.x = (low + high) / 2

                if abs(self.f(self.x)) < pow(10, -4):
                    return

    def print_function(self):
        if self.types == "exp":
            print("f(x) = " + str(self.a) + " * exp(x) + " + str(self.b))
        elif self.types == "cubic":
            print("f(x) = " + str(self.a) + " * x^3 + " + str(self.b) + " * x^2 + " + str(self.c) + " * x + " + str(
                self.d))
        elif self.types == "log":
            print("f(x) = " + str(self.a) + " * log(x) + " + str(self.b))

    def print_result(self):
        print("Binary Search")
        print("Solution : f( " + str(self.x) + " ) = " + str(self.f(self.x)) + " after " + str(
            self.iteration) + " iterations")


class main:
    def main(self):
        f1 = Numerical(types="exp", a=3.0, b=-5.0, x1=0, x2=1, tol=0)
        f2 = Numerical(types="cubic", a=2, b=-3, c=4, d=-5, x1=1, x2=2, tol=0.0001)
        f3 = Numerical(types="log", a=3.0, b=10.0, x1=0.0001, x2=0.05, tol=0.001)

execution = main()
execution.main()
