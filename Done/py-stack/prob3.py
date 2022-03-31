import sys

lines = sys.stdin.readlines()
s = []

for ln in lines:
    s.append(ln)


def solution(s):
    d = {  # 괄호 문자 매칭
        ')': '(',
        '}': '{',
        ']': '['
    }
    stack = []
    for line in range(len(s)):
        for c in range(len(s[line])):  # 문자열의 길이만큼 반복
            if s[line][c] in '({[':
                stack.append((s[line][c], c, line))  # 스택에 삽입 시 (문자, 인덱스) 튜플로 삽입
            elif s[line][c] in ')}]':
                if stack:  # 스택이 비어있지 않은 경우
                    top = stack.pop()
                    if d[s[line][c]] != top[0]:
                        if s[line][c] == ')':
                            return False, 1, c, line, s[line][c]
                        elif s[line][c] == '}':
                            return False, 2, c, line, s[line][c]
                        elif s[line][c] == ']':
                            return False, 3, c, line, s[line][c]
                else:  # 스택이 비어있을 경우
                    if s[line][c] == ')':
                        return False, 1, c, line, s[line][c]
                    elif s[line][c] == '}':
                        return False, 2, c, line, s[line][c]
                    elif s[line][c] == ']':
                        return False, 3, c, line, s[line][c]
    if len(stack):  # 정상종료했으나 스택에 남아있는 경우
        if stack[len(stack) - 1][0] == '(':
            return False, 4, stack[len(stack) - 1][1], stack[len(stack) - 1][2], stack[len(stack) - 1][0]
        elif stack[len(stack) - 1][0] == '{':
            return False, 5, stack[len(stack) - 1][1], stack[len(stack) - 1][2], stack[len(stack) - 1][0]
        elif stack[len(stack) - 1][0] == '[':
            return False, 6, stack[len(stack) - 1][1], stack[len(stack) - 1][2], stack[len(stack) - 1][0]
    else:
        return True, 0


rst = solution(s)

if rst[0]:
    print(1)
else:
    print(
        str("error " + str(rst[1]) + ": " + rst[4] + " at position " + str(rst[2] + 1) + " in line " + str(rst[3] + 1)))
