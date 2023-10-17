from src2.helper.printTree import printTree
from src2.src.parser import Parser
from src2.second.Vertex import VertexSecond


class ParserSecond(Parser):
    def __init__(self):
        super()

    def readfromConsole(self):
        file_name = input()
        file = open(file_name)
        if file is None:
            print('No such file.')
            return
        T = int(file.readline())

        for i in range(T):
            n = int(file.readline())

            for i in range(0, n):
                line = file.readline().split(' ')
                if len(line) == 2:
                    p, c = int(line[0]), int(line[1])

                    if i == 0:
                        child_vertex = VertexSecond(c)
                        self.get_tree().set_root(p, c)
                    else:
                        child_vertex = VertexSecond(c)
                        self.get_tree().add(p, c)
                elif len(line) == 3:
                    p, c, b = int(line[0]), int(line[1]), bool(line[2])
                    if i == 0:
                        child_vertex = VertexSecond(c)
                        self.get_tree().set_root(p, c)
                        self.get_tree().set_green(c, b)
                    else:
                        child_vertex = VertexSecond(c)
                        self.get_tree().add(p, c)
                        self.get_tree().set_green(c, b)

            tree = self.get_tree()

            root = tree.get_root()

            total = root.calculate_point()

            printTree(root)

            print(f"Total from vertex = {total+1}")
        return