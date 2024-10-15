class PIController:
    def __init__(self, P=2.0, I=0.1, Integrator=0, Integrator_max=500, Integrator_min=-500):
        self.Kp = P
        self.Ki = I
        self.Integrator = Integrator
        self.Integrator_max = Integrator_max
        self.Integrator_min = Integrator_min
        self.set_point = 0.0
        self.error = 0.0

    def update(self, error):
        self.error = error
        P_value = self.Kp * self.error

        self.Integrator += self.error
        if self.Integrator > self.Integrator_max:
            self.Integrator = self.Integrator_max
        elif self.Integrator < self.Integrator_min:
            self.Integrator = self.Integrator_min

        I_value = self.Integrator * self.Ki

        PI_value = P_value + I_value
        return PI_value

    def setPoint(self, set_point):
        self.set_point = set_point
        self.Integrator = 0

    def setKp(self, P):
        self.Kp = P

    def setKi(self, I):
        self.Ki = I

    def getPoint(self):
        return self.set_point

    def getError(self):
        return self.error

    def getIntegrator(self):
        return self.Integrator