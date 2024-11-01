'''
Created on Mar 22, 2023

@author: wuwei
'''

# from edu.wmich.cs1120.SP23.PA3.treeCalculation.src.tree import Tree
# from edu.wmich.cs1120.SP23.PA3.treeCalculation.src.vertex import Vertex
# from edu.wmich.cs1120.SP23.PA3.treeCalculation.helper.printTree import printTree

from src2.src.tree import Tree
from src2.src.vertex import Vertex
from src2.helper.printTree import printTree


class Parser:
    def __init__(self) -> None:
        self.__tree: Tree = None

    def get_tree(self):
        return self.__tree

    def set_tree(self, t):
        self.__tree = t

    def readfromConsole(self):

        n = int(input())

        for i in range(0, n):

            p, c = [int(x) for x in input().split()]
            if i == 0:
                child_vertex = Vertex(c)
                self.get_tree().set_root(p, child_vertex)
            else:
                child_vertex = Vertex(c)
                self.get_tree().add(p, child_vertex)

        tree = self.get_tree()

        root = tree.get_root()

        total = root.calculate_point()

        printTree(root)

        print(f"Total from vertex = {total}")
