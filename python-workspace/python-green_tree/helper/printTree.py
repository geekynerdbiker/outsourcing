'''
Created on Mar 22, 2023

@author: wuwei
'''

# from edu.wmich.cs1120.SP23.PA3.treeCalculation.src.tree import Vertex
from src2.src.tree import VertexSecond


def printTree(root: VertexSecond):
    stack = []  # (tabs, node)

    stack.append((0, root))
    while stack:

        tup = stack.pop()

        print("\t" * tup[0], end="")
        if tup[1].is_green is True:
            print(f"->{tup[1].get_vertex_info()}G")
        else:
            print(f"->{tup[1].get_vertex_info()}")

        for ele in tup[1].get_children():
            stack.append((tup[0] + 1, ele))
