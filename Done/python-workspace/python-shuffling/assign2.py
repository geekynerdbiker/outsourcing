import random

shuffling_array = []


def myran(num=1, seed=1):
    global shuffling_array

    if seed != 1:  # 씨드를 새로 설정
        random.seed = seed
        return

    if num == -1:  # Shuffling 방을 초기화
        shuffling_array = []
        return

    result = []

    if len(shuffling_array) == 0:  # Shuffling 방이 비어있을 경우
        for i in range(32):  # 원소 갯수를 32개로 설정
            shuffling_array.append(round(random.uniform(0, 1), 2))

    for i in range(num):  # num개의 난수 발생
        x = round(random.uniform(0, 1), 2)
        y = int(round(random.uniform(0, 1) * 10, 0))  # Y를 정수변환

        result.append(shuffling_array[y])  # i번째 방에 있던 난수를 꺼내 출력한다.
        shuffling_array[y] = x  # i번째 방에 X를 집어넣는다.

    return result


# Case 1
x = myran()
print("[Case 1] 1 Random Number")
print(x)

# Case 2
x = myran(100)
print("\n\n[Case 2] 100 Random Number")
print(x)

# Case 3
print("\n\n[Case 3] Before Init")
print(shuffling_array)
myran(-1)
print("\n[Case 3] After Init")
print(shuffling_array)

# Case 4
myran(seed=1038291)
