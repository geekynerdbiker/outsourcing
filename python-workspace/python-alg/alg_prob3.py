import math


class Network:
    def __init__(self):
        self.root = None

    def get_root(self):
        return self.root

    def set_root(self, root):
        self.root = root

    def inorder(self):
        return self.root.inorder()

    def insert(self, data, r):
        if self.root is None:
            self.root = Node(data)
        else:
            return self.root.insert(data, r)


class Node:
    def __init__(self, data):
        self.data = data
        self.children = []

    def get_data(self):
        return self.data

    def add_children(self, child):
        self.children.append(Node(child))

    def get_children(self):
        return self.children

    def inorder(self):
        ret = []
        ret += [self.data]
        for child in self.children:
            ret += child.inorder()

        return ret

    def insert(self, data, r):
        if get_dist(self.data, data) <= r:
            self.add_children(data)
            return True
        else:
            for child in self.children:
                if get_dist(child.data, data) <= r:
                    child.add_children(data)
                    return True
                else:
                    child.insert(data, r)
        return False


def get_dist(node1, node2):
    return math.sqrt((node1[0] - node2[0]) ** 2 + (node1[1] - node2[1]) ** 2 + (node1[2] - node2[2]) ** 2)


matrix = []
networks = []

# 정점의 갯수를 입력받는다.
n = int(input("Input number of partitions: "))

# 정점들을 입력받는다.
for i in range(n):
    x, y, z = map(int, input("Input partition " + str(i+1)).split(' '))
    matrix.append([x, y, z])

# 전파 도달거리를 입력받는다.
r = int(input("Input radio distance: "))

for i in range(len(matrix)):
    if i == 0:
        network = Network()
        network.set_root(Node(matrix[i]))
        networks.append(network)
        continue
    for j in range(len(networks)):
        if networks[j].insert(matrix[i], r) is False:
            network = Network()
            network.set_root(Node(matrix[i]))
            networks.append(network)
            break


print("Number of Networks: " + str(len(networks)) + "\n")

for i in range(len(networks)):
    print("[Network " + str(i+1) +"]")
    print(networks[i].inorder())
    print()