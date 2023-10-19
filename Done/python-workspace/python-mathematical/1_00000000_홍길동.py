# 문제에서 주어진 변수 선언
a1 = 10
r = 0.5
n = 3
tol = 1.0e-5


# 하위 문제 1번
def prob1_1(a):
    # r의 절대값이 1보다 작은 경우
    if 1 > r > -1:
        return a / (1 - r)
    # 그 외의 경우 발산
    else:
        return "divergence"


# 하위 문제 2번
def prob1_2(a, n):
    # n이 0이면 a(첫째 항) 반환 후 재귀 종료
    if n == 0:
        return a

    # 현재항 + 현재 -1번째 항 (재귀 호출)
    return a * (r ** n) + prob1_2(a, n - 1)


# 하위 문제 3번
def prob1_3(a, n):
    # 계산 결과의 차이가 tol보다 큰 경우 반복
    while prob1_1(a) - prob1_2(a, n) > tol:
        # 매 반복 마다 n을 1씩 증가
        n += 1

    # 반복 종료 후 a, r, n, tol 값 반환
    return a, r, n, tol


# 출력부
print("1.1 result\n")
print("first term : " + str(a1) + ", ratio : " + str(r) + "\n")
print("Sum obtained by mathematical calculation : " + str(prob1_1(a1)) + "\n")

print("1.2 result\n")
print("if n = " + str(n) + " -> S_n = " + str(prob1_2(a1, n - 1)) + "\n")

result1_3 = prob1_3(a1, n)
print("1.3 result\n")
print("tolerance : " + str(tol) + "\n")
print("n = " + str(result1_3[2] + 1) + ", S_n = " + str(prob1_2(a1, result1_3[2])))
print("error : " + str(prob1_1(a1) - prob1_2(a1, result1_3[2])))
