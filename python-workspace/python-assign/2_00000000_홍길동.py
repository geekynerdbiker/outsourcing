# 문제에서 주어진 변수 선언
p_1 = 100
d_1 = 2
v_1 = 0.1
x_1 = 7.5
pi = 3.141592


# 하위 문제 1번
def prob2_1(x):
    # x가 2.5보다 작은 경우
    if x <= 2.5:
        # d는 항상 d1
        return (d_1 / 2) ** 2 * pi
    # x가 12.5보다 큰 경우
    elif x >= 12.5:
        # d는 항상 d1 - 2
        return ((d_1 - 1) / 2) ** 2 * pi
    # 그 외
    else:
        # x의 위치에 따라 반지름 변화
        return ((d_1 - (0.05 * (12.5 - x) * 2)) / 2) ** 2 * pi


# 하위 문제 2번
def prob2_2(x):
    # 예시의 공식을 사용하여 속도 계산
    v_2 = (d_1 / 2) ** 2 * pi * v_1 / prob2_1(x)
    # 위에서 구한 속도를 이용하여 동압 계산
    dp = (1 / 2) * 1000 * (v_2 ** 2)
    # 동압을 이용하여 정압 계산
    p_2 = p_1 + (1 / 2) * 1000 * (v_1 ** 2) - dp

    # 속도, 정압, 동압, 정수압 반환
    return v_2, p_2, dp, p_2 + dp


# 하위 문제 3번
def prob2_3():
    # 저장할 파일 이름 지정
    filename = "prob_2_3_00000000_홍길동.csv"

    # 파일을 쓰기 전용으로 생성
    f = open(filename, "w")
    # 헤더 작성
    f.write("x(m),p2(Pa),dp(Pa),total(Pa)\n")

    # x는 0.0부터
    x = 0.0
    # 15.0까지 반복
    while x <= 15.0:
        # 하위 문제 2번과 마찬가지로 속도 계산
        v_2 = (d_1 / 2) ** 2 * pi * v_1 / prob2_1(x)
        # 동압 계산
        dp = (1 / 2) * 1000 * (v_2 ** 2)
        # 정압 계산
        p_2 = p_1 + (1 / 2) * 1000 * (v_1 ** 2) - dp
        # 파일에 x, 정압, 동압, 정수압 작성
        f.write(str(x) + "," + str(p_2) + "," + str(dp) + "," + str(p_2 + dp) + "\n")
        # x 증가
        x += 0.1

    # 파일을 저장하고 닫음
    f.close()

    # 파일 이름 반환
    return filename


# 출력부
print("2.1 result\n")
print("x = " + str(x_1) + " m")
print("A(x) = " + str(prob2_1(x_1)) + " m^ \n2")

print("2.2 result\n")
print("x = " + str(2.5) + " m")
print("v_x = " + str(prob2_2(2.5)[0]) + " m/s")
print("static_pressure_x = " + str(prob2_2(2.5)[1]) + " Pa")
print("dynamic_pressure_x = " + str(prob2_2(2.5)[2]) + " Pa\n")
print("bernoulli equation value = " + str(prob2_2(2.5)[3]) + "\n")

print("x = " + str(7.5) + " m")
print("v_x = " + str(prob2_2(7.5)[0]) + " m/s")
print("static_pressure_x = " + str(prob2_2(7.5)[1]) + " Pa")
print("dynamic_pressure_x = " + str(prob2_2(7.5)[2]) + " Pa\n")
print("bernoulli equation value = " + str(prob2_2(7.5)[3]) + "\n")

print("x = " + str(12.5) + " m")
print("v_x = " + str(prob2_2(12.5)[0]) + " m/s")
print("static_pressure_x = " + str(prob2_2(12.5)[1]) + " Pa")
print("dynamic_pressure_x = " + str(prob2_2(12.5)[2]) + " Pa\n")
print("bernoulli equation value = " + str(prob2_2(12.5)[3]) + "\n")

print("2.3 result\n")
print(prob2_3() + " is created")
