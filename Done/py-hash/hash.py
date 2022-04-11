from random import *
import time
from matplotlib import pyplot as plt


# Linear hash implements
class LinearHash:
    def __init__(self, size):
        self.size = size
        self.hashtable = [None for _ in range(size)]

    # Hasing
    def hash(self, key):
        index = key % self.size

        if self.hashtable[index] == None:
            return index
        else:
            # Linear probing
            while self.hashtable[index] != None:
                index = (index + 1) % self.size

            return index

    # Insert values after hash
    def insert(self, key):
        index = self.hash(key)
        self.hashtable[index] = key

    # Search value hash
    def search(self, key):
        index = key % self.size

        if self.hashtable[index] != key:
            # Quadratic probing
            while self.hashtable[index] != key and self.hashtable[index] != None:
                index = (index + 1) % self.size

        if self.hashtable[index] == key:
            return index
        else:
            return None


# Quadratic hash implements
class QuadraticHash:
    def __init__(self, size):
        self.size = size
        self.hashtable = [None for _ in range(size)]

    # Hasing
    def hash(self, key):
        index = key % self.size

        if self.hashtable[index] == None:
            return index
        else:
            i = 1
            while self.hashtable[(index + (i * i)) % self.size] != None:
                i += 1

            return (index + (i * i)) % self.size

    # Insert values after hash
    def insert(self, key):
        index = self.hash(key)
        self.hashtable[index] = key

    # Search value hash
    def search(self, key):
        index = key % self.size
        i = 0

        if self.hashtable[index] != key:
            # Quadratic probing
            while self.hashtable[(index + (i * i)) % self.size] != key and self.hashtable[
                (index + (i * i)) % self.size] != None:
                i += 1

        if self.hashtable[(index + (i * i)) % self.size] == key:
            return (index + (i * i)) % self.size
        else:
            return None

# Search value in array, sorted array
def search(arr, k):
    for i in range(len(arr)):
        if arr[i] == k:
            return i
        else:
            return False

# Generate random 1000 values.
N = [randint(0, 100000) for _ in range(1000)]
print('Initializing...')

# From 1000 to 10000
for M in range(1, 10):
    lh = LinearHash(M * 1000 * 2)
    qh = QuadraticHash(M * 1000 * 2)
    a = []

    # Insert values in Structures
    for n in range(M * 1000):
        k = randint(0, M * 1000)

        lh.insert(k)
        qh.insert(k)
        a.append(k)

    print('\nDo M=' + str(M * 1000))

    sa = sorted(a)

    # Start time check
    s1 = time.time()
    for n in N:
        rst = search(a, n)
    # End time check
    t1 = time.time() - s1
    print("Array: " + str(t1))

    # Start time check
    s2 = time.time()
    for n in N:
        rst = search(sa, n)
    # End time check
    t2 = time.time() - s2
    print("Sorted Array: " + str(t2))

    # Start time check
    s3 = time.time()
    for n in N:
        rst = lh.search(n)
    # End time check
    t3 = time.time() - s3
    print("Linear Probing: " + str(t3))

    # Start time check
    s4 = time.time()
    for n in N:
        rst = qh.search(n)
    # End time check
    t4 = time.time() - s4
    print("Quadratic Probing: " + str(t4))

    # Print Graph
    plt.plot([t1, t2, t3, t4], 'o')
    plt.show()
