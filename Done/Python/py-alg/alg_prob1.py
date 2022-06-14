def obst(p, q, n):
    E = [[0 for x in range(0, n + 1)] for y in range(0, n + 2)]
    W = [[0 for x in range(0, n + 1)] for y in range(0, n + 2)]
    R = [[0 for x in range(0, n + 1)] for y in range(0, n + 1)]

    for i in range(1, n + 1):
        E[i - 1][i] = 0
        E[i][i] = p[i]

        W[i - 1][i] = 0
        W[i][i] = p[i]

        R[i][i] = i
        R[i - 1][i] = 0

    for l in range(1, n):
        for i in range(1, n - l + 1):
            j = i + l
            E[i][j] = 1000
            W[i][j] = W[i][j - 1] + p[j] + q[j]
            for k in range(i, j + 1):
                if (E[i][k - 1] + E[k + 1][j] + W[i][j]) < E[i][j]:
                    E[i][j] = E[i][k - 1] + E[k + 1][j] + W[i][j]
                    R[i][j] = k
    return E, W, R


p = [0, 0.1, 0.09, 0.06, 0.05, 0.05, 0.04, 0.03]
q = [0.7, 0.12, 0.07, 0.07, 0.06, 0.05, 0.08, 0.06]

E, W, R = obst(p, q, len(p) - 1)

print("[Cost Table]")
for i in range(1, len(p) - 1):
    l = ""
    for j in range(1, len(p) - 1):
        l += str(E[i][j]) + " "
    print(l)


print("[Weight Table]")
for i in range(1, len(p) - 1):
    l = ""
    for j in range(1, len(p) - 1):
        l += str(W[i][j]) + " "
    print(l)

print("[Root Table]")
for i in range(1, len(p) - 1):
    l = ""
    for j in range(1, len(p) - 1):
        l += str(R[i][j]) + " "
    print(l)
