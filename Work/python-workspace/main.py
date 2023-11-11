import random

DEBUG = False

probe_distance = 5
rescued = 0


class Ship:
    def __init__(self):
        self.speed = 0
        self.position = 0
        self.angle = random.randint(1, 360)

    def move(self):
        self.position -= self.speed


class Crippled(Ship):
    def __init__(self):
        super().__init__()
        self.position = 600
        self.speed = 1
        self.rescued = False

    def isRescued(self):
        return self.rescued

    def rescue(self):
        self.rescued = True

    def move(self):
        super().move()
        if DEBUG:
            print("[Crippled] Angle:", str(self.angle), "Pos:", str(self.position))


class Probe(Ship):
    def __init__(self):
        super().__init__()
        self.position = 0
        self.speed = -20

    def probe(self, target: Crippled):
        if self.speed > 0 or target.isRescued():
            return False
        if self.angle == target.angle and self.position < target.position:
            if target.position - self.position <= probe_distance:
                return True
        return False

    def turnaround(self):
        self.speed *= -1

    def move(self):
        super().move()
        if DEBUG:
            print("[Probe] Angle:", str(self.angle), "Pos:", str(self.position))


class Rescue(Ship):
    def __init__(self, angle):
        super().__init__()
        self.position = 0
        self.speed = -5
        self.angle = angle

    def rescue(self, target: Crippled):
        if self.angle == target.angle and self.position < target.position:
            if target.position - self.position <= 5:
                return True
        return False

    def move(self):
        super().move()
        if DEBUG:
            print("[Rescue] Angle:", str(self.angle), "Pos:", str(self.position))


class HeadQuarter:
    def __init__(self):
        self.probes = []
        self.rescues = []
        self.crippled = []

    def sendProbe(self):
        self.probes.append(Probe())

    def sendRescue(self, angle):
        self.rescues.append(Rescue(angle))

    def addCrippled(self, crippled):
        self.crippled.append(crippled)

    def search(self, probe):
        for c in self.crippled:
            if probe.probe(c):
                probe.turnaround()
                print("Find Crippled in Angle:", probe.angle)

    def rescue(self, rescue):
        for c in self.crippled:
            if rescue.rescue(c):
                c.rescue()
                print("Rescued Crippled in Angle:", rescue.angle)

    def moveProbes(self):
        for i in range(len(self.probes)):
            p = self.probes.pop(0)

            if p.position >= 600:
                continue
            if p.speed > 0 and p.position == 0:
                print("Send Rescue to Angle:", p.angle)
                self.sendRescue(p.angle)
                continue

            self.search(p)
            p.move()
            self.probes.append(p)

    def moveRescues(self):
        for i in range(len(self.rescues)):
            r = self.rescues.pop(0)

            if r.position >= 600:
                continue

            self.rescue(r)
            r.move()
            self.rescues.append(r)

    def moveCrippled(self):
        global rescued
        for i in range(len(self.crippled)):
            c = self.crippled.pop(0)

            if c.position <= 0:
                continue
            if c.isRescued():
                rescued += 1
                print('Rescued:', rescued)
                continue

            c.move()
            self.crippled.append(c)

    def move(self):
        self.moveCrippled()
        self.moveProbes()
        self.moveRescues()


hq = HeadQuarter()

tick = 0
while (True):
    print("Iteration:", tick)
    if random.randint(1, 10) <= 1:
        hq.addCrippled(Crippled())
    hq.sendProbe()
    hq.move()
    tick += 1
