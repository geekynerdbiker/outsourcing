file = open("input.txt")

metro = {}

lines = file.readlines()

idx = 1
for line in lines:
    if line[-1] == '\n':
        line = line[:-1]
    line = line.split(",")

    if len(line) > 2:
        line[2] = line[2:]
        del line[3:]

    metro[line[0]] = [idx, line[1:]]
    idx += 1

depature = input("출발역: ")
while True:
    if depature not in metro:
        print("존재하지 않는 역입니다.")
        depature = input("출발역: ")
    else:
        break

destination = input('도착역: ')
while True:
    if destination not in metro:
        print("존재하지 않는 역입니다.")
        destination = input('도착역: ')
    else:
        break

dep_num = int(metro[depature][0])
des_num = int(metro[destination][0])

time_forward = 0
station_forward = 0
time_reverse = 0
station_reverse = 0
for m in metro:
    idx = int(metro[m][0])
    time = int(metro[m][1][0])

    if dep_num <= idx <= des_num or des_num <= idx <= dep_num:
        time_forward += time
        station_forward += 1
    else:
        time_reverse += time
        station_reverse += 1
print("\n[ 운행 역: ", min(station_forward, station_reverse), "개 ]")
print("[ 소요 시간: ", min(time_forward, time_reverse), "초 ]\n")

transfer = input("환승역: ")
while True:
    if destination not in metro:
        print("존재하지 않는 역입니다.")
        transfer = input("환승역: ")

    elif len(metro[transfer][1]) == 1:
        print("환승역이 아닙니다.")
        transfer = input("환승역: ")
    else:
        print("\n[ 환승가능 역 ]")
        for i in metro[transfer][1][1]:
            if len(i) == 1:
                print(i + "호선")
            else:
                print(i)
        break
