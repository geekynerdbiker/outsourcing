import math


def p1(df):
    distance = 0
    pool = df.values.tolist()
    path = []

    path.append(pool.pop(0))
    while len(pool) > 0:
        min_index = None
        min_dist = None

        for pool_i in range(len(pool)):
            node1 = path[len(path) - 1]
            node2 = pool[pool_i]
            dist = get_dist(node1, node2)

            if min_dist is None or min_dist > dist:
                min_dist = dist
                min_index = pool_i
        path.append(pool.pop(min_index))
        distance += min_dist

    route = []
    for i in range(len(path)):
        route.append(path[i][0])

    route.append(0)
    return route, distance


def get_dist(node1, node2):
    x1, x2, y1, y2 = node1[1], node2[1], node1[2], node2[2]
    dist = math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2)

    return dist


def p2(p):
    candidate = [[1000, 200], [500, 105], [1500, 400], [300, 50], [800, 500]]
    demand = [100, 150, 80, 50, 40, 10, 200, 100, 30, 20, 14, 20]
    sales_center = [38 + 43 + 16 + 24 + 32 + 14 + 42 + 35 + 15 + 40 + 22 + 38,
                    26 + 35 + 37 + 10 + 37 + 27 + 49 + 13 + 17 + 37 + 49 + 18,
                    42 + 19 + 19 + 18 + 22 + 46 + 10 + 13 + 13 + 27 + 47 + 17,
                    47 + 26 + 32 + 22 + 33 + 40 + 31 + 35 + 26 + 33 + 33 + 31,
                    42 + 25 + 18 + 49 + 39 + 21 + 22 + 39 + 50 + 29 + 10 + 10]

    solver = p.Solver.CreateSolver('GLOP')

    cost = []
    cont = []
    for i in range(5):
        cost.append(solver.NumVar(0, solver.infinity(), "cost" + str(i)))
        cont.append(solver.NumVar(0, solver.infinity(), "cont" + str(i)))

    objective = solver.Objective()
    for i in range(5):
        objective.SetCoefficient(cost[i], 1)
        objective.SetCoefficient(cont[i], 1)
    objective.SetMinimization()

    for i in range(5):
        for j in range(12):
            constraint = solver.Constraint(demand[j], solver.infinity())
            constraint.SetCoefficient(cont[i], sales_center[i])

    print(solver.Solve())

    minimum = int(1e9)
    min_index = 0
    for i in range(5):
        if minimum > cont[i].solution_value():
            minimum = cont[i].solution_value()
            min_index = i
        print("cont", str(i), "_opt: ", cont[i].solution_value())

    print("minimum cost: ", sales_center[min_index] + candidate[min_index][1])

    return
