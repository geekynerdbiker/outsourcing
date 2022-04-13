class Node:
    def __init__(self, key, height, left=None, right=None):
        self.key = key
        self.height = height
        self.left = left
        self.right = right

class AVL:
    def __init__(self):
        self.root = None

    def insert(self, key):
        self.root = self.insert_item(self.root, key)

    def insert_item(self, n, key):
        if n == None:
            return  Node(key, 1)
        if n.key > key:
            n.left = self.insert_item(n.left, key)
        elif n.key < key:
            n.right = self.insert_item(n.right, key)
        n.height = max(self.height(n.left), self.height(n.right))+1
        return self.balance(n)

    def balance(self, n):
        if self.bf(n) > 1:
            if self.bf(n.left) < 0:
                n.left = self.rotate_left(n.left)
            n = self.rotate_right(n)

        elif self.bf(n) < -1:
            if self.bf(n.right) > 0:
                n.right = self.rotate_right(n.right)
            n = self.rotate_left(n)
        return n

    def bf(self, n):
        return self.height(n.left)-self.height(n.right)

    def rotate_right(self, n):
        x = n.left
        n.left = x.right
        x.right = n
        n.height = max(self.height(n.left), self.height(n.right)) + 1
        x.height = max(self.height(x.left), self.height(x.right)) + 1
        return x

    def rotate_left(self, n):
        x = n.right
        n.right = x.left
        x.left = n
        n.height = max(self.height(n.left), self.height(n.right)) + 1
        x.height = max(self.height(x.left), self.height(x.right)) + 1
        return x

    def preorder(self, n):
        print(str(n.key),' ', end="")
        if n.left:
            self.preorder(n.left)
        if n.right:
            self.preorder(n.right)

    def inorder(self, n):
        if n.left:
            self.inorder(n.left)
        print(str(n.key), ' ', end="")
        if n.right:
            self.inorder(n.right)

if __name__=="__main__":
    aa = AVL()
    aa.insert(10)
    aa.insert(20)
    aa.insert(30)
    aa.insert(40)
    aa.insert(50)
    aa.insert(29)
