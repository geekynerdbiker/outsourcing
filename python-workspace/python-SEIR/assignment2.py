import math


def update_spread(S, E, I, R, alpha=0.2, beta=0.2, gamma=0.2):
    # To-do: 입력 받은 Susceptible, Exposed, Infectious, Recovered 비율을 통해 하루 뒤의 비율을 계산하여 반환
    """
    :param S: susceptible 비율
    :param E: exposed 비율
    :param I: infectious 비율
    :param R: recovered 비율
    :param alpha: 1/잠복기(일)
    :param beta: 전염율
    :param gamma: 회복율 = 1/평균 감염 기간(일)
    :return: 새로운 S, E, I, R 비율
    """
    assert math.isclose(S + E + I + R, 1.0)  # S, E, I, R 총합이 1.0이 되도록 제한, 삭제하지 마세요!

    # Answer
    dSdt = -1 * beta * S * (I + E)
    dEdt = beta * S * (I + E) - alpha * E
    dIdt = alpha * E - gamma * I
    dRdt = gamma * I

    return S + dSdt, E + dEdt, I + dIdt, R + dRdt
    pass


def run_epidemic_simul(total_days=100, S=0.95, E=0, I=0.05, R=0):
    # To-do:
    # 1. 입력 받은 초기 비율부터 total_days 동안 전염병을 전파시킨 결과를 다른 함수에서 사용가능하도록 반환하세요.
    # 2. 매번(하루 간격으로) 전염병 전파 결과를 아래와 같이 출력하세요. 단, 각 비율은 소수점 3자리까지 나타내세요.
    # X일차 상황: S = XX, I = XX, E = XX, R = XX
    # 출력 예시: 50일차 상황: S = 0.234, I = 0.029, E=0.045, R = 0.692
    """   
    :param total_days: 총 시뮬레이션 할 일 수
    :param S: 초기 정상 상태(S) 비율
    :param E: 초기 노출 상태(E) 비율
    :param I: 초기 감염 상태(I) 비율
    :param R: 초기 회복 상태(R) 비율
    :return: total_days 동안의 전염병 전파 결과
    """

    # Answer
    data = []
    for i in range(total_days + 1):
        print("%d일차 상황: S = %.3lf, E = %.3lf, I = %.3lf, R = %.3lf" % (i, S, E, I, R))
        data.append([S, E, I, R])
        S, E, I, R = update_spread(S, E, I, R)
    return data
    pass


def print_status(data, day=0):
    # To-do:
    # 입력 받은 날(day)의 감염자 수 비율을 아래와 같이 출력하세요. 단, 각 비율은 소수점 3자리까지 나타내세요.
    # X일차 상황: S = XX, I = XX, E = XX, R = XX
    # 출력 예시: 50일차 상황: S = 0.234, I = 0.029, E=0.045, R = 0.692
    """
    :param data: run_epidemic_simul을 통해 얻은 전염병 전파 기록
    :param day: 관심 있는 날
    """

    # Answer
    print("%d일차 상황: S = %.3lf, E = %.3lf, I = %.3lf, R = %.3lf" % (
    day, data[day][0], data[day][1], data[day][2], data[day][3]))
    return data[day]
    pass


def pick(data, pick_rate=False):
    # To-do: 
    # pick_rate 변수에 따라 감염자 수 혹은 감염자 수 증가율이 가장 컸던 날을 계산해서 반환하세요.
    # 1. pick_rate = False, 감염자(Infectious) 수가 가장 많았던 날을 계산해서 반환하세요.
    # 2. pick_rate = True, 감염자(Infectious) 수 증가율이 가장 컸던 날을 계산해서 반환하세요.
    """
    :param data: run_epidemic_simul을 통해 얻은 전염병 전파 기록
    :param pick_rate: 출력 할 종류 결정
    :return: pick 날짜 (0~total_days 중 한 날짜) 또는 증가율이 가장 컸던 날짜
    """

    # Answer
    maxValue, maxIndex = 0, 0
    if pick_rate:
        for i in range(1, len(data)):
            if data[i][2] - data[i - 1][2] > maxValue:
                maxValue = data[i][2] - data[i - 1][2]
                maxIndex = i
        return maxIndex - 1
    else:
        for i in range(len(data)):
            if data[i][2] > maxValue:
                maxValue = data[i][2]
                maxIndex = i
        return maxIndex
    pass


if __name__ == '__main__':
    # To-do: 위의 함수들을 활용해서 아래
    # 1. 50일차 상황 출력하기
    # 2. 감염자 수가 가장 많았던 날짜 출력하기
    # 3. 감염자 수 증가율이 가장 컸던 날짜 출력하기

    # Answer
    data = run_epidemic_simul(100)
    print_status(data, 100)
    print(pick(data, False))
    print(pick(data, True))
    pass
