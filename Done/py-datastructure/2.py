import sys


class MaxHeap:
    def __init__(self, maxsize):

        self.maxsize = maxsize
        self.size = 0
        self.Heap = [0] * (self.maxsize + 1)
        self.Heap[0] = sys.maxsize
        self.FRONT = 1

    def parent(self, pos):

        return pos // 2

    def leftChild(self, pos):

        return 2 * pos

    def rightChild(self, pos):

        return (2 * pos) + 1

    def isLeaf(self, pos):

        if pos >= (self.size // 2) and pos <= self.size:
            return True
        return False

    def swap(self, fpos, spos):

        self.Heap[fpos], self.Heap[spos] = (self.Heap[spos],
                                            self.Heap[fpos])

    def maxHeapify(self, pos):
        if not self.isLeaf(pos):
            if (self.Heap[pos] < self.Heap[self.leftChild(pos)] or
                    self.Heap[pos] < self.Heap[self.rightChild(pos)]):

                if (self.Heap[self.leftChild(pos)] >
                        self.Heap[self.rightChild(pos)]):
                    self.swap(pos, self.leftChild(pos))
                    self.maxHeapify(self.leftChild(pos))

                else:
                    self.swap(pos, self.rightChild(pos))
                    self.maxHeapify(self.rightChild(pos))

    def insert(self, element):

        if self.size >= self.maxsize:
            return
        self.size += 1
        self.Heap[self.size] = element

        current = self.size

        while (self.Heap[current] >
               self.Heap[self.parent(current)]):
            self.swap(current, self.parent(current))
            current = self.parent(current)

    def Print(self):
        n, exp = 1, 2
        s = ""
        for i in range(1, self.size + 1):
            s += '[' + str(self.Heap[i]) + '] '
            if i == n:
                s += '\n'
                n = 2 ** exp - 1
                exp += 1

        if s[-1] == '\n':
            s = s[:len(s) - 1]
        print(s)

    def extractMax(self):

        popped = self.Heap[self.FRONT]
        self.Heap[self.FRONT] = self.Heap[self.size]
        self.size -= 1
        self.maxHeapify(self.FRONT)

        return popped

    def printAll(self):
        s = ""
        for i in range(1, self.size + 1):
            s += '[' + str(self.Heap[i]) + '] '

        print(s)


maxHeap = MaxHeap(15)

while True:
    inp = int(input("input: "))
    if inp == 999:
        maxHeap.printAll()
        break
    else:
        maxHeap.insert(inp)
        maxHeap.Print()
