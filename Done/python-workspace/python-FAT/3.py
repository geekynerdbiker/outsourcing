def solution(s):
    l = [0 for k in range(len(s) + 1)]
    for score in s:
        for i in range(score+1):
            if i > len(s):
                break
            l[i] += 1

    score = 0
    for i in range(len(s) + 1):
        if i == l[i]:
            score = i
    return score


i = input()
s = []
for c in i:
    if c.isdigit():
        s.append(int(c))

print(solution(s))
