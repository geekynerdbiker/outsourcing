k = int(input())

coin = [1, 2, 5, 7]
case = [0 for i in range(len(coin))]

coin.reverse()
case.reverse()

while k > 0:
    for i in range(len(coin)):
        if k - coin[i] < 0:
            continue
        k -= coin[i]
        case[i] += 1

for i in range(len(coin)):
    print(str(coin[i]) + " coin: " + str(case[i]))
