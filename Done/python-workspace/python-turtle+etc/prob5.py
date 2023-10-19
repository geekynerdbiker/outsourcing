import random

animals = ['Cheetah', 'Tiger', 'Jaguar', 'Lion', 'Horse']
speed = []
time = []
for i in range(5):
    speed.append(random.randint(30000, 100000) / 3600)
    time.append(100 / speed[i])

for a, t in zip(animals, time):
    print(a + ': ' + str(t) + 'sec')
