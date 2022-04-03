from random import *
import time
from matplotlib import pyplot as plt


# Linear
class LinearHash:
    def __init__(self, size):
        self.size = size
        self.hashtable = [None for _ in range(size)]

    def hash(self, key):
        index = key % self.size

        if self.hashtable[index] == None:
            return index
        else:
            while self.hashtable[index] != None:
                index = (index + 1) % self.size

            return index

    def insert(self, key):
        index = self.hash(key)
        self.hashtable[index] = key

    def search(self, key):
        index = key % self.size

        if self.hashtable[index] != key:
            while self.hashtable[index] != key and self.hashtable[index] != None:
                index = (index + 1) % self.size

        if self.hashtable[index] == key:
            return index
        else:
            return None


# Quadratic
class QuadraticHash:
    def __init__(self, size):
        self.size = size
        self.hashtable = [None for _ in range(size)]

    def hash(self, key):
        index = key % self.size

        if self.hashtable[index] == None:
            return index
        else:
            i = 1
            while self.hashtable[(index + (i * i)) % self.size] != None:
                i += 1

            return (index + (i * i)) % self.size

    def insert(self, key):
        index = self.hash(key)
        self.hashtable[index] = key

    def search(self, key):
        index = key % self.size
        i = 0

        if self.hashtable[index] != key:
            while self.hashtable[(index + (i * i)) % self.size] != key and self.hashtable[
                (index + (i * i)) % self.size] != None:
                i += 1

        if self.hashtable[(index + (i * i)) % self.size] == key:
            return (index + (i * i)) % self.size
        else:
            return None


def search(arr, k):
    for i in range(len(arr)):
        if arr[i] == k:
            return i
        else:
            return False


N = [randint(0, 100000) for _ in range(1000)]
print('Initializing...')

for M in range(1, 10):
    lh = LinearHash(M * 1000 * 2)
    qh = QuadraticHash(M * 1000 * 2)
    a = []

    for n in range(M * 1000):
        k = randint(0, M * 1000)

        lh.insert(k)
        qh.insert(k)
        a.append(k)

    print('\nDo M=' + str(M * 1000))

    sa = sorted(a)

    s1 = time.time()
    for n in N:
        rst = search(a, n)
    t1 = time.time() - s1
    print("Array: " + str(t1))

    s2 = time.time()
    for n in N:
        rst = search(sa, n)
    t2 = time.time() - s2
    print("Sorted Array: " + str(t2))

    s3 = time.time()
    for n in N:
        rst = lh.search(n)
    t3 = time.time() - s3
    print("Linear Probing: " + str(t3))

    s4 = time.time()
    for n in N:
        rst = qh.search(n)
    t4 = time.time() - s4
    print("Quadratic Probing: " + str(t4))

    plt.plot([t1, t2, t3, t4], 'o')
    plt.show()