def solve(posts, cows):
    posts, fences = sort_posts(posts)
    touches = {fence: 0 for fence in fences}

    for cow in cows:
        start, end = cow[:2], cow[2:]

        if start == end:
            continue
        if start not in fences:
            points = get_possible_points(fences, start)
            start = min(points, key=lambda p: (abs(p[0] - start[0]) + abs(p[1] - start[1])))
        if end not in fences:
            points = get_possible_points(fences, end)
            end = min(points, key=lambda p: (abs(p[0] - end[0]) + abs(p[1] - end[1])))
        if start == end:
            continue

        clockwise_dist = 0
        counter_dist = 0
        index_start = fences.index(start)

        i = index_start
        while fences[i] != end:
            clockwise_dist += abs(fences[i][0] - fences[i - 1][0]) + abs(fences[i][1] - fences[i - 1][1])
            i = (i + 1) % len(fences)

        i = index_start
        while fences[i] != end:
            counter_dist += abs(fences[i][0] - fences[(i + 1) % len(fences)][0]) + abs(
                fences[i][1] - fences[(i + 1) % len(fences)][1])
            i = (i - 1) % len(fences)

        if clockwise_dist < counter_dist:
            step = 1
        else:
            step = -1

        i = index_start
        while fences[i] != end:
            touches[fences[i]] += 1
            i = (i + step + len(fences)) % len(fences)
        touches[end] += 1

    return touches


def get_dist(p1, p2):
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])


def sort_posts(points):
    stack = [points[0]]
    visited, fences = [], []

    while stack:
        position = stack.pop()
        if position not in visited:
            visited.append(position)

            if len(fences) != 0:
                x = fences[-1][0]
                y = fences[-1][1]

                if x == position[0]:
                    if y < position[1]:
                        for i in range(y + 1, position[1]):
                            fences.append((x, i))
                    else:
                        for i in range(y - 1, position[1], -1):
                            fences.append((x, i))

                if y == position[1]:
                    if x < position[0]:
                        for i in range(x + 1, position[0]):
                            fences.append((i, y))
                    else:
                        for i in range(x - 1, position[0], -1):
                            fences.append((i, y))
            fences.append(position)

        not_visited = points.copy()
        for v in visited:
            not_visited.remove(v)
        for next_position in get_possible_points(not_visited, position):
            if next_position not in visited:
                stack.append(next_position)

    x = fences[-1][0]
    y = fences[-1][1]

    if x == fences[0][0]:
        if y < fences[0][1]:
            for i in range(y + 1, fences[0][1]):
                fences.append((x, i))
        else:
            for i in range(y - 1, fences[0][1], -1):
                fences.append((x, i))

    if y == fences[0][0]:
        if x < fences[0][0]:
            for i in range(x + 1, fences[0][0]):
                fences.append((i, y))
        else:
            for i in range(x - 1, fences[0][0], -1):
                fences.append((i, y))

    return visited, fences


def get_possible_points(points, position):
    closest_points = []
    x, y = position

    closest_points.append(
        min([(px, py) for px, py in points if px == x], key=lambda p: (abs(y - p[1]), p[1]), default=None))
    closest_points.append(
        min([(px, py) for px, py in points if py == y], key=lambda p: (abs(x - p[0]), p[0]), default=None))

    return [p for p in closest_points if p]


n, p = map(int, input().split())
posts, cows = [], []

for i in range(p):
    posts.append(tuple(map(int, input().split())))
for i in range(n):
    cows.append(tuple(map(int, input().split())))

ans = solve(posts, cows)
for p in posts:
    print(ans[p])

'''
5 4
3 1
1 5
3 5
1 1
2 1 1 5
1 5 3 4
3 1 3 5
2 1 2 1
3 2 3 3
'''

'''
2 8
1 1
1 2
0 2
0 3
0 0
0 1
2 3
2 0
1 1 2 1
1 0 1 3
'''

'''
1 12
0 0
2 0
2 1
1 1
1 2
3 2
3 3
1 3
1 4
2 4
2 5
0 5
2 2 0 2
'''
