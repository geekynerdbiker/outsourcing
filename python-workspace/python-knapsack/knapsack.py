maxWeight = 7
rowCount = 4
weight = [0, 6, 4, 3, 5]
money = [0, 13, 8, 6, 12]


def dynamic_programming():
    array = [[0 for _ in range(maxWeight + 1)] for _ in range(rowCount + 1)]  # 빈 배열을 만들고 모두 0으로
    for row in range(1, rowCount + 1):  # 1~4개 (4회)
        print(row, '개 -->', end='')
        for col in range(1, maxWeight + 1):  # 1colg ~ 7colg
            if weight[row] > col:  # 물건의 무게가 열보다 크면 == 물건이 가방에 안 들어가면
                array[row][col] = array[row - 1][col]
            else:  # 물건의 부피가 s보다 작거나 같으면
                value1 = money[row] + array[row - 1][col - weight[row]]
                value2 = array[row - 1][col]
                array[row][col] = max(value1, value2)
            print('%2d' % array[row][col], end='')
        print()
    return array[rowCount][maxWeight]


def brute_force():
    maxValue = 0
    for i in range(1, rowCount + 1):  # 물품들의 갯수만큼 반복
        weights, value = 0, 0  # 각 반복에 대해서 현재 무게와 가치를 0으로 초기화
        for j in range(i, rowCount + 1):  # 첫번째 물품부터 반복
            if weights + weight[j] <= maxWeight:  # 현재 무게에 물건을 넣었을 때 최대 무게를 초과하지 않으면
                weights += weight[j]  # 배낭에 물품 추가
                value += money[j]  # 상응하는 가치 추가
        if maxValue < value:  # 최대 가치보다 현재 가치가 더 크면
            maxValue = value  # 현재 가치를 최대 가치로 갱신
    return maxValue


def greedy():
    wm = []  # (무게, 가치) 형식의 튜플로 저장할 리스트
    for i in range(1, rowCount + 1):  # 각 물품들에 대해
        wm.append((weight[i], money[i]))  # 튜플로 묶어서 리스트에 저장
    wm = sorted(wm, key=lambda x: x[1] / x[0], reverse=True)  # 단위 무게 당 가치에 대해 내림차순 정렬

    weights, value = 0, 0  # 각 반복에 대해서 현재 무게와 가치를 0으로 초기화
    for element in wm:  # 단위 무게 당 높은 가치를 지니는 물건부터 탐색
        if weights + element[0] <= maxWeight:  # 현재 무게에 물건을 넣었을 때 최대 무게를 초과하지 않으면
            weights += element[0]  # 배낭에 물품 추가
            value += element[1]  # 상응하는 가치 추가
    return value


maxValue = dynamic_programming()
print()
print('배낭에 담을 수 있는 보석의 최대 가격 -->', maxValue, '억원')

maxValue = brute_force()
print()
print('배낭에 담을 수 있는 보석의 최대 가격 -->', maxValue, '억원')

maxValue = greedy()
print()
print('배낭에 담을 수 있는 보석의 최대 가격 -->', maxValue, '억원')
