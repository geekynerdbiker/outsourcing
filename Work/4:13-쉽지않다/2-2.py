arvt = [] # 도착 시간
judgt = [] # 심사 시간
k = int(input()) # k

for i in range(k): # 입력 받는 부분
    arvt_idx, judgt_idx = map(int, input().split())
    arvt.insert(i, arvt_idx)
    judgt.insert(i, judgt_idx)

waitt = [0 for i in range(k + 1)]
pure_wait_time = [0 for i in range(k+1)]
sum_arvt = [0 for i in range(k + 1)]

num = 0
for i in range(len(arvt)):
    if arvt[i] != 0:
        num += arvt[i]
    sum_arvt[i] += num

# 처음 들어가는 경우 최초 도착시간 + 심사시간
k1 = sum_arvt[0] + judgt[0]
k2 = sum_arvt[1] + judgt[1]

for i in range(2, k):
# 누적 도착시간 + 대기시간 + 심사시간
    waitt[i] = sum_arvt[i] + min(abs(sum_arvt[i] - k1), abs(sum_arvt[i] - k2)) + judgt[i]
    # 누적 도착시간과 K1, K2시간의 차이 중 작은 것
    pure_wait_time[i] = min(abs(sum_arvt[i] - k1), abs(sum_arvt[i] - k2))
    if k1 > k2:
        k2 = waitt[i]
    else:
        k1 = waitt[i]

print(round(sum(pure_wait_time)/k, 2))
