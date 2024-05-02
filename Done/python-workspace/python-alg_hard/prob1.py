def solve(k, t):
    time = 0
    index = 0

    farmers = []
    available = ['0'] * k

    for i in range(k):
        farmers.append(t[i])
        index += 1

    while index < len(t):
        availables = get_available(farmers)
        if availables != 0:
            if availables == 1:
                farmers[farmers.index(0)] = t[index]
                index += 1
            else:
                l = [i for i, value in enumerate(farmers) if value == 0]
                for i in l:
                    available[i] = '1'
                    farmers[i] = t[index]
                    index += 1

        else:
            time += min(farmers)
            elepse_time(farmers, min(farmers))

    l = [i for i, value in enumerate(farmers) if value == min(farmers)]
    for i in l:
        available[i] = '1'

    return time + min(farmers), ''.join(available)


def get_available(farmers):
    available = 0
    for f in farmers:
        if f == 0:
            available += 1
    return available


def elepse_time(farmers, time):
    for i in range(len(farmers)):
        farmers[i] -= time


n, k = map(int, input().split())
t = list(map(int, input().split()))

ans = solve(k, t)
print(ans[0])
print(ans[1])

'''
6 3
3 1 4159 2 6 5
'''
