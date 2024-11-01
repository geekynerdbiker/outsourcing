import random as rd
import numpy as np

import matplotlib.pyplot as plt
import seaborn as sb


def GetProbability(Prob):
    if rd.random() <= Prob:
        return True  # showed up
    else:
        return False  # didn't show up


def FlightSimulation(Sold, Prob):
    n = 0
    for i in range(1, Sold):
        if GetProbability(Prob):
            n = n + 1

    return n


# simulating the net Revenue per flight
def NetProfitSimulation(Profit, TixPrice, Loss, SeatCap, Sold, Prob, LastMinuteProfit):
    Total = FlightSimulation(Sold, Prob)
    # no one bumped from flight if less or equal folks show up than for the number of seats we have
    if Total <= SeatCap:
        return Profit * Total
    else:
        Overbooked = Total - SeatCap
        return (Total * LastMinuteProfit) - (Loss * Overbooked)


Profit = 250  # Profit per ticket
TixPrice = 500
Loss = 1.25 * TixPrice  # Loss due to overbooking penality for each overbooked seat
SeatCap = 180  # Seat capacity of the airplane
LastMinuteProfit = 1.5 * TixPrice

Iter = 100
Max = 20
Profits = np.zeros(shape=(Iter, Max + 1))
Prob = 0.95

# Running the simulation
for tickets_overbooked in range(0, Max):
    Sold = SeatCap + tickets_overbooked
    for i in range(1, Iter):
        Profits[i, tickets_overbooked] = NetProfitSimulation(Profit, TixPrice, Loss, SeatCap, Sold, Prob,
                                                             LastMinuteProfit)

sb.set()
sb.set(rc={'figure.figsize': (15, 20)})
ax = sb.boxplot(data=Profits, notch=True)
plt.xlabel("Tickets Oversold")
plt.ylabel("Profits")
plt.ylim(0, 160000)
