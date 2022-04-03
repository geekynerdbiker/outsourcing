from Numerical import Numerical


class main:
    def main(self):
        f1 = Numerical(types="exp", a=3.0, b=-5.0, x1=0, x2=1, tol=0)
        f2 = Numerical(types="cubic", a=2, b=-3, c=4, d=-5, x1=1, x2=2, tol=0.0001)
        f3 = Numerical(types="log", a=3.0, b=10.0, x1=0.0001, x2=0.05, tol=0.001)


execution = main()
execution.main()
