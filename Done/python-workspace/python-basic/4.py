"""
Prob 4
"""

athlete = [["Tammy", 86.4, 1.74, "F", 10.93], ["John", 103.3, 1.86, "M", 10.35], ["David", 96, 1.89, "M", 9.98],
           ["Viviana", 68.2, 1.58, "F", 11.23], ["Tom", 80.2, 1.77, "M", 10.67]]
speedteam = []

for person in athlete:
    if person[3] == "F":
        print(person[0])

for person in athlete:
    if person[3] == "F":
        if person[4] < 11:
            speedteam.append(person)
    elif person[3] == "M":
        if person[4] < 10.5:
            speedteam.append(person)
print(speedteam)
