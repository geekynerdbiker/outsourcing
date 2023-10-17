# ---------------------------------------------------
#                       PART A
# ---------------------------------------------------

"""
[ Time Complexity Summary ]

def insert(self, key, value): O(n^2)
def modify(self, key, value): O(n)
def remove(self, key): O(n)
def search(self, key): O(n)
def capacity(self): O(1)
def __len__ (self): O(n)
"""


class SortedTable:
    # packaging the key-value pair into one object
    class Record:
        def __init__(self, key, value):
            self.key = key
            self.value = value

    def __init__(self, cap=32):
        # this initializes a list of of capacity length with None
        self.the_table = [None for i in range(cap)]
        self.cap = cap

    def insert(self, key, value):
        if (self.search(key) != None):
            return False

        if (len(self) == self.cap):
            # increase the capacity if list is full
            new_table = [None for i in range(self.cap * 2)]  # n + 3
            for i in range(self.cap):  # n + 1
                new_table[i] = self.the_table[i]  # n + 2
            self.the_table = new_table
            self.cap *= 2

        self.the_table[len(self)] = self.Record(key, value)
        size = len(self)

        # Bubble Solt Below O(n^2)
        for i in range(0, size - 1):  # n - 1
            for j in range(0, size - 1 - i):  # n
                if (self.the_table[j].key > self.the_table[j + 1].key):
                    tmp = self.the_table[j]
                    self.the_table[j] = self.the_table[j + 1]
                    self.the_table[j + 1] = tmp
        return True

    """
    def insert(self, key, value)
    
    Total Time Complexity = (n+3) + (n+1) + (n+2) + {(n-1) * (n)} = (3n+6) + (n^2-n)
    T(n) = 0(n^2)
    """

    def modify(self, key, value):
        i = 0
        while (i < len(self) and self.the_table[i].key != key):  # n
            i += 1
        if (i == len(self)):
            return False
        else:
            self.the_table[i].value = value
            return True

    """
    def modify(self, key, value)
    
    Total Time Complexity = (n)
    T(n) = O(n)
    """

    def remove(self, key):
        i = 0
        size = len(self)
        while (i < size and self.the_table[i].key != key):  # n
            i += 1
        if (i == size):
            return False
        while (i + 1 < size):  # n - 1
            self.the_table[i] = self.the_table[i + 1]
            i += 1
        self.the_table[i] = None
        return True

    """
    def remove(self, key)

    Total Time Complexity = (n) + (n-1) = (2n-1)
    T(n) = O(n)
    """

    def search(self, key):
        i = 0
        size = len(self)
        while i < size and self.the_table[i].key != key:  # n
            i += 1
        if i == size:
            return None
        else:
            return self.the_table[i].value

    """
    def search(self, key)

    Total Time Complexity = (n)
    T(n) = O(n)
    """

    def capacity(self):
        return self.cap  # 1

    """
    def capacity(self)

    Total Time Complexity = (1) 
    T(n) = O(1)
    """

    def __len__(self):
        i = 0
        count = 0
        while (i < len(self.the_table)):  # n
            if (self.the_table[i] != None):
                count += 1
            i += 1
        return count

    """
    def __len__(self)

    Total Time Complexity = (n)
    T(n) = O(n)
    """


# ---------------------------------------------------
#                       PART B
# ---------------------------------------------------

"""
Suggestion 1: Use another sorting algorithm instead of bubble sort. ( e.g. Quick Sort( O(n log n) ), Heap Sort( O(n log n) ) )
Suggestion 2: Add len variable in initialize time. It makes the time complexity of __len__ to 1. 
"""


# ---------------------------------------------------
#                       PART C
# ---------------------------------------------------

class ChainingHash:
    class Record:
        def __init__(self, key=None, value=None):
            self.key = key
            self.value = value

    def __init__(self, cap=32):
        self.cap = cap
        self.the_table = [[] for i in range(self.cap)]
        self.len = 0

    def insert(self, key, value):
        self.len += 1
        h = hash(key) % self.cap

        for v in self.the_table[h]:
            if key == v[0]:
                self.len -= 1
                return False

        if (1.0 * self.len / self.cap) > 1:
            self.rehash()

        self.the_table[h].append((key, value))
        return True

    def modify(self, key, value):
        h = hash(key) % self.cap

        for i, v in enumerate(self.the_table[h]):
            if key == v[0]:
                self.the_table[h][i] = (key, value)
                return True
        return False

    def remove(self, key):
        h = hash(key) % self.cap
        for i, v in enumerate(self.the_table[h]):
            if key == v[0]:
                del self.the_table[h][i]
                self.len -= 1
                return True
        return False

    def search(self, key):
        h = hash(key) % self.cap
        for v in self.the_table[h]:
            if key == v[0]:
                return v[1]
        return None

    def capacity(self):
        return self.cap

    def __len__(self):
        return self.len

    def rehash(self):
        self.len = 1
        self.cap = self.cap * 2

        t = self.the_table
        self.the_table = [[] for i in range(self.cap)]
        for item in t:
            for i in item:
                self.insert(i[0], i[1])
