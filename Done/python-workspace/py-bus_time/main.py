import numpy as np
import pandas as pd

# 파일 이름, 반복 횟수를 인자로 받아 실행
def func(filename, epoch):
    # 데이터 프레임 평식으로 파일을 연다
    file = pd.read_excel('bus/'+filename+'.xlsx')
    # 누적합 및 데이터 저장을 위한 리스트
    total = []

    print('[ 버스 운행 일자:', filename, ']')

    # 평균값 저장을 위한 리스트
    result = []
    # 인자로 받은 반복 횟수만큼 반복
    for i in range(epoch):
        # 한 세트를 담을 리스트. 한 세트 -> 각각의 배차 간격에 따른 리스트 데이터
        set = []

        # 20분 부터 40분 까지 2분 간격으로 배차간격을 조정하며 반복
        for arrival in range(20, 40, 2):
            # 현재 배차 간격에 따른 데이터를 저장할 리스트
            data = [0, 0, 0, 0, 0]
            # 5시부터 23시까지 총 18시간 운행
            running_hour = 18
            # 1시간 = 60분
            minutes = 60
            # 현재 시간 = 0 -> 5시 0분
            t = 0

            # 도착 시간들을 저장할 리스트
            arrival_time = []
            # 공석의 갯수
            empty = 0
            # 시간동안 반복
            while t < running_hour * minutes:
                # 버스의 도착시간을 배차간겨, 표준편차를 3으로 난수 생성
                arrival_time.append(np.random.normal(loc=arrival, scale=3))
                # 버스 총 탑승가능 좌석을 30명이라고 가정
                empty += 30
                # 도착 시간만큼 현재시간 증가
                t += arrival

            # 전체 도착 시간 합계
            total_time = sum(arrival_time)
            # 총 도착한 버스의 수
            num_bus = len(arrival_time) - 1

            # 엑셀 데이터에 따른 하루 총 탑승객 수
            c3 = file['합계'][0]

            # 데이터에 저장
            data[0] = arrival
            data[1] = num_bus
            data[2] = empty
            data[3] = c3
            data[4] = empty - c3
            # 세트에 배차간격마다의 데이터 추가
            set.append(np.array(data))
        # 전체 데이터에 각 세트 추가
        total.append(np.array(set))

    # 결괏값을 세트와 같은 크기의 numpy 행렬로 생성 -> 행렬 덧셈을 하기 위함
    result = np.zeros(np.array(set).shape)

    # 반복 횟수만큼 데이터에 누적합
    for i in range(epoch):
        result += total[i]
    # 평균 계산을 위해 반복횟수로 모든 값을 나누어줌
    result /= epoch
    # 출력
    print('반복 횟수:', epoch)
    for i in range(10):
        print('\t배차간격:', result[i][0], '   ', end='')
        print('버스 수:', result[i][1], '   ', end='')
        print('공석 수:', result[i][2], '   ', end='')
        print('승객 수:', result[i][3], '   ', end='')
        print('잔여석 수:', result[i][4] , '   ', end='')
        print()

    # 가공된 평균값 데이터 반환
    return result

# 파일 이름, 반복횟수에 따른 모든 데이터를 저장할 리스트
data = []

# 각각의 파일별로 1, 10, 100회 반복
data.append(np.array(func('230417', 1)))
data.append(np.array(func('230417', 10)))
data.append(np.array(func('230417', 100)))

data.append(np.array(func('230418', 1)))
data.append(np.array(func('230418', 10)))
data.append(np.array(func('230418', 100)))

data.append(np.array(func('230419', 1)))
data.append(np.array(func('230419', 10)))
data.append(np.array(func('230419', 100)))

data.append(np.array(func('230420', 1)))
data.append(np.array(func('230420', 10)))
data.append(np.array(func('230420', 100)))

# 결과를 저장할 행렬 초기화
result = np.zeros((10, 5))

# 함수로부터 받아 저장한 데이터들을 누적함
for i in range(len(data)):
    result += data[i]

# 함수의 총 실행 횟수로 나눔
result /= 12

# 결과 출력
print(result)

# 제가 실행했을 때에는, 배차간격이 30분 일 때 공석의 평균 갯수가 가장 0에 가까우므로, 배차간격을 30분으로 할 떄가 가장 효율적이라는 결과가 나왔습니다.
# pdf와 마찬가지로 입석을 전혀 고려하지 않고 작성한 프로그램입니다.