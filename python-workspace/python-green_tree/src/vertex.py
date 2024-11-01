'''
Created on Mar 22, 2023

@author: wuwei
'''


class Vertex:

    def __init__(self, name) -> None:
        self.__children = []
        self.__parent = None
        self.__name = name

    def get_index(self):
        return self.__name

    def get_parent(self):
        return self.__parent

    def get_children(self):
        return self.__children

    def set_index(self, i):
        self.__name = i

    def set_parent(self, new_parent):
        self.__parent = new_parent

    def add_child(self, v):
        # new_v = Vertex(v)

        self.__children.append(v)

        return v

    def calculate_point(self):

        if self.__children == []:
            return 1

        else:

            total = 0

            total += self.calculate_Num_Vertices(self)
            for v in self.__children:
                total += v.calculate_point()

            return total

    def calculate_Num_Vertices(self, v):

        total = 1
        if v.get_children() == []:
            return 1

        else:
            for ele in v.get_children():
                total += ele.calculate_Num_Vertices(ele)

            return total

    def get_vertex_info(self):
        return self.__name
