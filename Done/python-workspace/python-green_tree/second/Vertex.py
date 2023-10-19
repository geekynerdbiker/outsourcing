from src2.src.vertex import Vertex


class VertexSecond(Vertex):
    def __init__(self, name):
        super().__init__(name)
        self.is_green = False
        return

    def calculate_point(self):
        return self.calculate_point_recursive(self)

    def calculate_point_recursive(self, v):
        total = 0
        for c in v.get_children():
            total += v.calculate_point_recursive(c)
        return total + v.calculate_Num_vertices()

    def calculate_Num_vertices(self):
        return self.calculate_Num_vertices_recursive(self)

    def calculate_Num_vertices_recursive(self, v):
        total = 0
        for c in v.get_children():
            total += v.calculate_Num_vertices_recursive(c)

        if self.is_green is True:
            return 2 * (total + 1)
        return total + 1

    def add_child(self, v):
        vertex = VertexSecond(v)
        vertex.parent = self.get_index()
        self.get_children().append(vertex)
        return vertex

    def set_green(self, b):
        self.is_green = b
