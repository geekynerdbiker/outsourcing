import sys

sys.setrecursionlimit(1000000)


def DFS(curr, isroot):
    global node_cnt, discover

    node_cnt += 1
    discover[curr] = node_cnt

    low[curr] = discover[curr]
    child = 0

    if curr == len(adj_list) - 1:
        return low[curr]
    for next in adj_list[curr]:
        if discover[next] == 0:
            child += 1

            mindisc = DFS(next, 0)
            if not isroot and mindisc >= discover[curr]:
                cut[curr] = 1

            low[curr] = min(low[curr], mindisc)

        else:
            low[curr] = min(low[curr], discover[next])

    if isroot and child > 1:
        cut[curr] = 1

    return low[curr]


def print_graph():
    print("\n====================")
    print("print_graph()")
    print("====================")

    for i in range(len(graph)):
        big_children = []
        small_children = []

        line = "node " + str(i + 1) + ": "

        for j in range(len(graph)):
            if graph[i][j] != 0:
                if i < j:
                    big_children.append(j + 1)
                else:
                    small_children.append(j + 1)

        for j in range(len(big_children)):
            line += str(big_children[j]) + ", "

        for j in range(len(small_children)):
            line += str(small_children[j]) + ", "

        line = line[:-2]
        print(line)


def print_num(arr):
    print("\n====================")
    print("print_num()")
    print("====================")

    for i in range(len(graph)):
        line = "node " + str(i + 1) + ": " + str(arr[i] + 1)
        print(line)


def print_low(arr):
    print("\n====================")
    print("print_low()")
    print("====================")

    for i in range(len(graph)):
        line = "low "
        line += str(i + 1) + ": " + str(arr[i + 1])
        print(line)


def print_points(cut):
    print("\n====================")
    print("print_points()")
    print("====================")

    line = "articulation point: "
    for v in range(n):
        if cut[v] == 1:
            line += str(v + 1) + ", "

    line = line[:-2]
    print(line)


n = int(input())

graph = [[0 for col in range(n)] for row in range(n)]

for x in range(n):
    ln = list(input())

    for y in range(n):
        graph[x][y] = int(ln[y])

adj_list = [[] for _ in range(n + 1)]
discover = [0 for _ in range(n + 1)]
cut = [0 for _ in range(n + 1)]
node_cnt = 0
low = [0 for _ in range(n + 1)]

for x in range(n):
    for y in range(n):
        if graph[x][y] == 1:
            adj_list[x + 1].append(y + 1)
            adj_list[y + 1].append(x + 1)

for v in range(1, n + 1):
    if discover[v] == 0:
        DFS(v, 1)

start = int(input())
if start < 0:
    exit(0)

print_graph()
print_num(discover)
print_low(low)
print_points(cut)
