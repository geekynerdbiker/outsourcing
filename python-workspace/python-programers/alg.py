import sys


# 두 물품의 조합으로 구매가능 한 금액이 예산과 일치할 때마다 가짓수 추가.
def solution1(a, b, budget):
    # 정답 갯수
    answer = 0

    for i in range(budget):
        # a 물풀 갯수 i개의 가격이 예산을 초과하면 중지
        if i * a >= budget:
            break
        for j in range(budget):
            # b 물풀 갯수 j개의 가격이 예산을 초과하면 중지
            if j * b >= budget:
                break

            # a 물풀 i개와 b 물품 j개의 가격이 예산과 맞아 떨어지면 정답 1증가
            if (budget - (i * a + j * b)) == 0:
                answer += 1

    return answer


# 구매일은 판매일보다 빠를 수 없기 때문에 모든 날에 대한 판매가격 - 구매가격을 비교하여 가장 큰 값을 찾음.
def solution2(n, v):
    # 최솟값을 찾기위해 정답을 가장 작은 정수로 설정
    rst = -sys.maxsize - 1

    for i in range(n):
        for j in range(n):
            # 판매일 i가 구매일 j와 같거나 크면 다음 날짜로 이동
            if i == j or i > j:
                continue

            # 정답과 (판매일 - 구매일)의 값을 비교하여 큰 값을 저장
            rst = max(rst, v[i] - v[j])

    return rst


# 현재 지점에서 다음 토핑까지의 거리를 정방향, 역방향 동시 탐색.
def solution3(topping, testing):
    # 정답, 정방향, 역방향, 현재 위치 초기화
    rst, inverse, reverse, curr = 0, 0, 0, 0

    # 이동거리
    l = 0

    # 4개의 토핑을 다 맛보면 종료
    while curr != len(testing):
        # 정방향으로 이동 중 맛 볼 토핑의 위치에 도착
        if topping[inverse] == testing[curr]:
            # 정답에 이동거리 누적
            rst += l
            # 다음 토핑으로 이동
            curr += 1
            # 역방향 인덱스 정방향으로 이동
            reverse = inverse
            # 이동거리 초기화
            l = 0
            continue

        # 역방향으로 이동 중 맛 볼 토핑의 위치에 도착
        elif topping[reverse] == testing[curr]:
            # 정답에 이동거리 누적
            rst += l
            # 다음 토핑으로 이동
            curr += 1
            # 역방향 인덱스 정방향으로 이동
            inverse = reverse
            # 이동거리 초기화
            l = 0
            continue

        # 정방향, 역방향, 이동거리 인덱스 증
        inverse += 1
        reverse -= 1
        l += 1

    return rst


def solution4(monsters, bullets):
    rst = 0

    for i in range(len(bullets)):
        for j in range(len(monsters)):
            if monsters[j] == [0, 0]:
                continue
            # 총알과 몬스터의 x 좌표가 모두 0일 때
            elif bullets[i][0] == 0 and monsters[j][0] == 0:
                rst += 1
                monsters[j] = [0, 0]
                break
            # 총알과 몬스터의 y 좌표가 모두 0일 때
            elif bullets[i][1] == 0 and monsters[j][1] == 0:
                rst += 1
                monsters[j] = [0, 0]
                break
            # 총알이나 몬스터의 x 좌표가 0일 경우 기울기를 비교할 수 없으므로 중지
            elif bullets[i][0] == 0 or monsters[j][0] == 0:
                continue
            # 그 외의 경우 기울기 비교
            elif bullets[i][1] / bullets[i][0] == monsters[j][1] / monsters[j][0]:
                rst += 1
                monsters[j] = [0, 0]
                break

    if rst == 0:
        return -1
    return rst


# prob 1
print("prob 1: a=3000 b=5000 budget = 23000")
print(solution1(3000, 5000, 23000))

# prob 2
print("prob 2: n=10 v=[3, 1, 4, 1, 5, 9, 2, 6, 5, 3]")
print(solution2(10, [3, 1, 4, 1, 5, 9, 2, 6, 5, 3]))

# prob 3
print("prob 3: topping=[2, 1, 3, 1, 2, 4, 4, 3] testing=[1, 2, 3, 4]")
print(solution3([2, 1, 3, 1, 2, 4, 4, 3], [1, 2, 3, 4]))

# prob 4
print("prob 4: ")
print(solution4([[2, 3], [4, 5], [3, -3], [2, -4], [3, -6], [-3, -3], [-5, 0], [-4, 4]],
                [[4, 1], [4, 6], [1, -2], [-4, -4], [-3, 0], [-4, 4]]))
