'''
Created on Mar 22, 2023

@author: wuwei
'''

# from edu.wmich.cs1120.SP23.PA3.treeCalculation.src.vertex import Vertex
from src2.second.Vertex import VertexSecond


class Tree:
    def __init__(self) -> None:
        self.__root: VertexSecond = None

    def get_root(self):
        return self.__root

    def set_root(self, r: int, c: VertexSecond):
        root_vertex = VertexSecond(r)
        child_vertex = root_vertex.add_child(c)
        child_vertex.set_parent(root_vertex)
        self.__root = root_vertex

    def set_green(self, v: int, s: bool):
        vertex = self.searchVertex(v)
        vertex.is_green = True

    def add(self, u: int, v: VertexSecond) -> VertexSecond:
        u_vertex = self.searchVertex(u)
        child_vertex = u_vertex.add_child(v)
        child_vertex.set_parent(u_vertex)

    def searchVertex(self, v: int) -> VertexSecond:
        stack = []
        stack.append(self.__root)

        while stack:
            vertex: VertexSecond = stack.pop()

            if vertex.get_vertex_info() == v:
                return vertex

            for ele in vertex.get_children():
                stack.append(ele)

        # Didnt find node
        return None
