s = input()


def solution(s):
    d = {  # 괄호 문자 매칭
        ')': '(',
        '}': '{',
        ']': '['
    }
    stack = []
    for c in range(len(s)):  # 문자열의 길이만큼 반복
        if s[c] in '({[':
            stack.append((s[c], c))  # 스택에 삽입 시 (문자, 인덱스) 튜플로 삽입
        elif s[c] in ')}]':
            if stack:  # 스택이 비어있지 않은 경우
                top = stack.pop()
                if d[s[c]] != top[0]:
                    if s[c] == ')':
                        return False, 1, c
                    elif s[c] == '}':
                        return False, 2, c
                    elif s[c] == ']':
                        return False, 3, c
            else:  # 스택이 비어있을 경우
                if s[c] == ')':
                    return False, 1, c
                elif s[c] == '}':
                    return False, 2, c
                elif s[c] == ']':
                    return False, 3, c
    if len(stack):  # 정상종료했으나 스택에 남아있는 경우
        if stack[len(stack) - 1][0] == '(':
            return False, 4, stack[len(stack) - 1][1]
        elif stack[len(stack) - 1][0] == '{':
            return False, 5, stack[len(stack) - 1][1]
        elif stack[len(stack) - 1][0] == '[':
            return False, 6, stack[len(stack) - 1][1]
    else:
        return True, 0


rst = solution(s)

if rst[0]:
    print(1)
else:
    print(str(rst[2]) + " error" + str(rst[1]))
