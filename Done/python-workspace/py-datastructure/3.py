from collections import defaultdict
from heapq import heapify, heappop, heappush


class Node:
    def __init__(self, value):
        self.data = value


class Graph:
    def __init__(self):
        self.graph = {}
        self.v_list = {}
        self.edge = []
        self.total = 0

    def create(self, v, data, weight):
        node = Node(data)
        if v not in self.graph:
            self.graph[v] = []
            self.graph[v].append((node, weight))

    def sort_edge(self, network):
        temp = []
        for v1, v2, cost in network:
            temp.append((cost, v1, v2))
        temp.sort()
        return temp

    def find(self, v2):
        for v1, lst in self.v_list.items():
            if v2 == v1:
                return v1
            if v2 in self.v_list[v1]:
                return v1
        return -1

    def union(self, s1, s2):
        if s1 < s2:
            self.v_list[s1].append(s2)
            self.v_list[s1].extend(self.v_list[s2])
            del self.v_list[s2]
        else:
            self.v_list[s2].append(s1)
            self.v_list[s2].extend(self.v_list[s1])
            del self.v_list[s1]

    def kruskal(self):
        for v1, v2, cost in network:
            if v1 not in self.v_list:
                self.v_list[v1] = []
            if v2 not in self.v_list:
                self.v_list[v2] = []
        print('set list=', self.v_list)
        sort_network = self.sort_edge(network)

        print('cost sorted (cost, v1, v2) ', sort_network)
        for cost, v1, v2 in sort_network:
            print('(', v1, ',', v2, ')', 'cost = ', cost)
            s1 = self.find(v1)
            s2 = self.find(v2)
            print('v1 set:', s1, 'v2 set:', s2)
            if s1 == s2:
                print('the same set. rejected for cycle.')
                continue
            self.edge.append((v1, v2, cost))
            self.total += cost
            self.union(s1, s2)
            print(self.v_list)

    def prim(self, start):
        mst = list()
        adj_edges = defaultdict(list)
        for n1, n2, cost in network:
            adj_edges[n1].append((n1, n2, cost))
            adj_edges[n2].append((n2, n1, cost))

        connected = set()
        connected.add(start)
        candidate_list = adj_edges[start]
        heapify(candidate_list)

        while candidate_list:
            cost, n1, n2 = heappop(candidate_list)
            if n2 not in connected:
                mst.append((n1, n2, cost))

                for edge in adj_edges[n2]:
                    if edge[2] not in connected:
                        heappush(candidate_list, edge)

        return mst


g = Graph()

network = [(1, 2, 5), (1, 4, 3), (2, 5, 10), (4, 5, 6), (4, 6, 7), (3, 5, 8), (5, 7, 13), (3, 7, 11), (6, 7, 15)]

for v, node, weight in network:
    g.create(v, node, weight)
print(g.prim(1))
