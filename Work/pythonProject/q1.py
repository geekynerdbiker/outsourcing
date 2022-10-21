# DO NOT DELETE/EDIT THIS LINE OF CODE, AS IT IS USED TO PROVIDE ACCESS TO
# WORKING IMPLEMENTATIONS OF THE FUNCTIONS FROM Q1

characteristics = ["intelligence", "beauty", "strength", "speed"]
superwug_genome = [1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0]
gene_zones = [2, 1, 2, 3, 3, 1, 3, 3, 0, 0, 2, 2, 0, 1, 0, 1]


def genome2features(genome):
    # TODO: Write your function here
    result = [0, 0, 0, 0]

    for i in range(len(gene_zones)):
        if genome[i] == superwug_genome[i]:
            result[gene_zones[i]] += 1

    ans = [False, False, False, False]

    for i in range(len(result)):
        if result[i] == 4:
            ans[i] = True
    return ans


def report_population(population):
    # TODO: Write your function here
    dict = {}
    for i in population:
        features = genome2features(i[0])
        gender = i[1]
        tup = (features[0], features[1], features[2], features[3], gender)

        if tup in dict:
            dict[tup] += 1
        else:
            dict[tup] = 1

    dict = sorted(dict.items(), reverse=True, key=lambda x: x[0])
    return dict


def rank(wug):
    # TODO: Write your function here
    ans = 0
    for feature in genome2features(wug[0]):
        if feature is True:
            ans += 1

    return ans


def insert_ranked(population, new_wug, limit=64):
    # TODO: Write your function here
    if new_wug is not None:
        population.append(new_wug)
    population.sort(reverse=True, key=lambda x: rank(x))

    while len(population) > limit:
        population.remove(population[len(population) - 1])


def proliferate(population, limit=64):
    # TODO: Write your function here
    for i in range(len(population)):
        for j in range(len(population[i][0])):
            clone = population[i][0].copy()
            gender = population[i][1]

            if clone[j] == 0:
                clone[j] = 1
            else:
                clone[j] = 0

            population.append((clone, gender))
    insert_ranked(population, None, limit)


wug1 = ([0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1], 'F')
wug2 = ([0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1], 'M')
wug3 = ([1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1], 'F')

population1 = [wug1]
proliferate(population1)
print(population1)
print(report_population(population1))
# [((False, False, False, False, 'F'), 17)]

population2 = [wug2, wug3]
proliferate(population2)
print(population2)

print(report_population(population2))

# [([1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1], 'F'),
#  ([0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1], 'M'),
#  ([1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1], 'F'),
#  ([1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1], 'M'),
#  ([0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1], 'M'),
#  ([0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1], 'M'),
#  ([0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1], 'M'),
#  ([0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1], 'M'),
#  ([0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1], 'M'),
#  ([0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1], 'M'),
#  ([0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1], 'M'),
#  ([0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1], 'M'),
#  ([0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1], 'M'),
#  ([0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1], 'M'),
#  ([0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0], 'M'),
#  ([0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1], 'F'),
#  ([1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1], 'F'),
#  ([1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1], 'F'),
#  ([1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1], 'F'),
#  ([1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1], 'F'),
#  ([1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1], 'F'),
#  ([1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1], 'F'),
#  ([1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1], 'F'),
#  ([1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1], 'F'),
#  ([1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1], 'F'),
#  ([1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0], 'F'),
#  ([0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1], 'M'),
#  ([0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1], 'M'),
#  ([0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1], 'M'),
#  ([0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1], 'M'),
#  ([1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1], 'F'),
#  ([1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1], 'F'),
#  ([1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1], 'F'),
#  ([1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1], 'F')]

a = ()
print(len(a))