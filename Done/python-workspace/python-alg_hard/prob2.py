def solve(n, s):
    ans = [0] * (n + 1)

    for k in range(1, n + 1):
        for l in range(1, k + 1):
            p = set()
            for i in range(n - k + 1):
                mer = s[i:i + k]
                min_sub = mer[:l]
                for j in range(1, k - l + 1):
                    sub = mer[j:j + l]
                    if sub < min_sub:
                        min_sub = sub
                loc = mer.find(min_sub)
                p.add(i + loc)
            ans[len(p)] += 1
    return ans


n = int(input())
s = input()

ans = solve(n, s)
for v in range(1, n + 1):
    print(ans[v])

'''
8
AGTCAACG
'''