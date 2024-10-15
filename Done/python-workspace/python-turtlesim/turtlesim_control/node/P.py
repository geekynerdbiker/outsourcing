class PController:
    def __init__(self, P=2.0):
        self.Kp = P
        self.set_point = 0.0
        self.error = 0.0

    def update(self, error):
        self.error = error
        P_value = self.Kp * self.error
        return P_value

    def setPoint(self, set_point):
        self.set_point = set_point

    def setKp(self, P):
        self.Kp = P

    def getPoint(self):
        return self.set_point

    def getError(self):
        return self.error