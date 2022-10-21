def solution(s):
    answer = 0

    str = []
    for i in range(len(s)):
        tmp = ''
        alphabets = []
        for j in range(i, len(s)):
            tmp += s[j]

            if tmp in str:
                alphabets.append(s[j])
                continue
            elif s[j] in alphabets:
                break
            else:
                alphabets.append(s[j])
                str.append(tmp)
                answer += 1

    return answer



print(solution('abac'))
print(solution('abcd'))
print(solution('zxzxz'))
