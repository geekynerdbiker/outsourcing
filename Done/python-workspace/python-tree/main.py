import sys


class Parser:
    def __init__(self):
        self.tree = None
        return

    def readfromConsole(self):
        T = int(input())

        for i in range(T):
            self.tree = Tree()
            n = int(sys.stdin.readline())
            for j in range(n - 1):
                a, b = map(int, sys.stdin.readline().split())
                self.tree.add(a, b)

            if i + 1 < T:
                k = input()
            self.tree.pretty_printing()
        return


class Tree:
    def __init__(self):
        self.__root = None
        return

    def search(self, u):
        target = []
        return self.search_recursive(u, self.__root, target)

    def add(self, u, v):
        if self.__root is None:
            self.__root = Vertex(u)

        n = self.search(u)

        if n is not None:
            n.add_child(v)
        return

    def search_recursive(self, u, v, target):
        if v.index == u:
            target.append(v)

        for c in v.children:
            self.search_recursive(u, c, target)

        if len(target) > 0:
            return target[0]
        return None

    def pretty_printing(self):
        print("Total from vertex = " + str(self.__root.calculate_point()) + "\n")


class Vertex:
    index = 0

    def __init__(self, v):
        self.index = v
        self.children = []
        self.parent = 0
        return

    def calculate_point(self):
        return self.calculate_point_recursive(self)

    def calculate_point_recursive(self, v):
        total = 0
        for c in v.children:
            total += v.calculate_point_recursive(c)
        return total + v.calculate_Num_vertices()

    def calculate_Num_vertices(self):
        return self.calculate_Num_vertices_recursive(self)

    def calculate_Num_vertices_recursive(self, v):
        total = 0
        for c in v.children:
            total += v.calculate_Num_vertices_recursive(c)
        return total + 1

    def add_child(self, v):
        vertex = Vertex(v)
        vertex.parent = self.index
        self.children.append(vertex)
        return


p = Parser()
p.readfromConsole()

'''
2
10
1 2
2 3
3 4
3 5
3 6
1 7
7 8
7 9
7 10

5
1 2
1 3
2 4
2 5
'''
