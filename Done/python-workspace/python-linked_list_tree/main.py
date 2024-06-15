class ListNode:
    def __init__(self, data=None):
        self.data = data
        self.next = None


class LinkedList:
    def __init__(self):
        self.head = None

    def insert(self, data):
        new_node = ListNode(data)
        if self.head is None or self.head.data >= new_node.data:
            new_node.next = self.head
            self.head = new_node
        else:
            current = self.head
            while current.next is not None and current.next.data < new_node.data:
                current = current.next
            new_node.next = current.next
            current.next = new_node

    def delete(self, word):
        if not self.head:
            return

        if self.head.word == word:
            self.head = self.head.next
            return

        current = self.head
        while current.next:
            if current.next.word == word:
                current.next = current.next.next
                return
            current = current.next

    def display(self):
        current = self.head
        words = []
        while current:
            words.append(current.data)
            current = current.next
        return words


class TreeNode:
    def __init__(self, char):
        self.char = char
        self.word_list = LinkedList()
        self.left = None
        self.right = None


class AlphabetTree:
    def __init__(self):
        self.root = None
        self._initialize_tree()

    def _initialize_tree(self):
        for char in "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ":
            self.insert(char)

    def insert(self, char):
        if self.root is None:
            self.root = TreeNode(char)
        else:
            self._insert(self.root, char)

    def _insert(self, node, char):
        if char < node.char:
            if node.left is None:
                node.left = TreeNode(char)
            else:
                self._insert(node.left, char)
        elif char > node.char:
            if node.right is None:
                node.right = TreeNode(char)
            else:
                self._insert(node.right, char)

    def find_node(self, char):
        return self._find_node(self.root, char)

    def _find_node(self, node, char):
        if node is None:
            return None
        if char == node.char:
            return node
        elif char < node.char:
            return self._find_node(node.left, char)
        else:
            return self._find_node(node.right, char)

    def insert_word(self, word):
        if not word:
            return
        first_char = word[0].upper()
        node = self.find_node(first_char)
        if node:
            node.word_list.insert(word)

    def delete_word(self, word):
        if not word or not self.root:
            return
        char = word[0].upper()
        node = self.find_node(self.root, char)
        if node:
            node.word_list.delete(word)
            if not node.word_list.head:
                self._delete_node(self.root, char)

    def _delete_node(self, root, char):
        if not root:
            return root

        if char < root.char:
            root.left = self._delete_node(root.left, char)
        elif char > root.char:
            root.right = self._delete_node(root.right, char)
        else:
            if not root.left:
                return root.right
            elif not root.right:
                return root.left
            else:
                successor = self._find_minimum(root.right)
                root.char = successor.char
                root.right = self._delete_node(root.right, successor.char)
        return root

    def _find_minimum(self, root):
        current = root
        while current.left:
            current = current.left
        return current
    
    def display_tree(self, node):
        if node:
            self.display_tree(node.left)
            print(f"{node.char}: {node.word_list.display()}")
            self.display_tree(node.right)


tree = AlphabetTree()

with open('word_tiny.txt', 'r') as f:
    lines = f.readlines()
    for line in lines:
        tree.insert_word(line.strip())

tree.display_tree(tree.root)
