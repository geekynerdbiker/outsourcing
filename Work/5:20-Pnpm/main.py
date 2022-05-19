import random


class Array:
    array = []
    size = 0

    def __init__(self, data):
        self.array = data
        self.size = len(data)

    @classmethod
    def zeros(cls, length):
        cls.array = [0 for _ in range(length)]
        cls.size = len(cls.array)

    @classmethod
    def randint(cls, length):
        cls.array = [random.randrange(0, 100000) for _ in range(length)]
        cls.size = len(cls.array)

    def __add__(self, other):
        if other.size != self.size:
            return None

        rst_arr = []
        for i in range(self.size):
            rst_arr.append(self.array[i] + other.array[i])

        return rst_arr

    def __sub__(self, other):
        if other.size != self.size:
            return None

        rst_arr = []
        for i in range(self.size):
            rst_arr.append(self.array[i] - other.array[i])

        return rst_arr

    def dot(self, other):
        if other.size != self.size:
            return None

        rst = 0
        for i in range(self.size):
            rst += self.array[i] * other.array[i]

        return rst


class Matrix(Array):
    def __init__(self, matrix):
        self.matrix = matrix
        self.size = (len(matrix), len(matrix[0]))

    @classmethod
    def zeros(cls, row, col):
        cls.matrix = [[0 for _ in range(col)] for _ in range(row)]
        cls.size = (len(cls.matrix), len(cls.matrix[0]))

    @classmethod
    def randint(cls, row, col):
        cls.matrix = [[random.randrange(0, 100000) for _ in range(col)] for _ in range(row)]
        cls.size = (len(cls.matrix), len(cls.matrix[0]))

    @classmethod
    def eye(cls, size):
        cls.matrix = [[0 for _ in range(size)] for _ in range(size)]
        cls.size = (len(cls.matrix), len(cls.matrix[0]))

        for i in range(size):
            for j in range(size):
                if i == j:
                    cls.matrix[i][j] = 1
        # cls.__init__(matrix)

    def __add__(self, other):
        if other.size != self.size:
            return None

        rst_arr = []
        for i in range(self.size[0]):
            for j in range(self.size[1]):
                rst_arr.append(self.array[i][j] + other.array[i][j])

        return rst_arr

    def __sub__(self, other):
        if other.size != self.size:
            return None

        rst_arr = []
        for i in range(self.size[0]):
            for j in range(self.size[1]):
                rst_arr.append(self.array[i][j] - other.array[i][j])

        return rst_arr

    def dot(self, other):
        if other.size != self.size:
            return None

        rst_arr = []
        for i in range(self.size[0]):
            for j in range(self.size[1]):
                rst_arr.append(self.array[i][j] * other.array[i][j])

        return rst_arr


# a_matrix = [[1, 2, 3, 4], [5, 6, 7, 8]]
# A = Matrix(a_matrix)
# A = Matrix.randint(3,4)
# A = Array([1,0,0,1])
# B = Array([2,1,0,1])

# A = Array([1,2,3,4])
A = Array.randint(4)
print(A)
