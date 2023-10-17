class TreeNode:
    def __init__(self, val, left=None, right=None, height=1):
        self.val = val
        self.left = left
        self.right = right
        self.height = height


class AVLtree:
    def __init__(self, val):
        self.root = TreeNode(val)
        self.preorder_list = []
        self.inorder_list = []
        self.postorder_list = []

    def insert(self, val):
        self.root = self._insert_node(self.root, val)

    def _insert_node(self, cur, val):
        if not cur:
            return TreeNode(val)
        elif val < cur.val:
            cur.left = self._insert_node(cur.left, val)
        elif val > cur.val:
            cur.right = self._insert_node(cur.right, val)

        cur.height = 1 + max(self._get_height(cur.left),
                             self._get_height(cur.right))

        balance = self._get_balance(cur)
        if balance > 1 and val > cur.left.val:
            cur.left = self._left_rotate(cur.left)
            cur = self._right_rotate(cur)

        elif balance > 1 and val < cur.left.val:
            cur = self._right_rotate(cur)

        elif balance < -1 and val > cur.right.val:
            cur = self._left_rotate(cur)

        elif balance < -1 and val < cur.right.val:
            cur.right = self._right_rotate(cur.right)
            cur = self._left_rotate(cur)
        return cur

    def _find_predecessor(self, cur):
        if cur.right:
            return self._find_predecessor(cur.right)
        else:
            return cur.val

    def _left_rotate(self, cur):
        v = cur
        w = cur.right
        t = w.left
        cur = w
        w.left = v
        v.right = t
        v.height = 1 + max(self._get_height(v.left), self._get_height(v.right))
        w.height = 1 + max(self._get_height(w.left), self._get_height(w.right))
        return cur

    def _right_rotate(self, cur):
        v = cur
        w = cur.left
        t2 = w.right
        cur = w
        w.right = v
        v.left = t2
        v.height = 1 + max(self._get_height(v.left), self._get_height(v.right))
        w.height = 1 + max(self._get_height(w.left), self._get_height(w.right))
        return cur

    def _get_height(self, cur):
        if not cur:
            return 0
        return cur.height

    def _get_balance(self, cur):
        if not cur:
            return 0
        return self._get_height(cur.left) - self._get_height(cur.right)

    def traverse(self):
        return self._print(self.root, [])

    def _print(self, cur, result):
        if cur:
            self._print(cur.left, result)
            result.append(cur.val)
            self._print(cur.right, result)

            if cur.left is None and cur.right is None:
                print(f'val:{cur.val}')
            elif cur.right is None:
                print(f'val:{cur.val}, left:{cur.left.val}')
            elif cur.left is None:
                print(f'val:{cur.val}, right:{cur.right.val}')
            else:
                print(f'val:{cur.val}, left:{cur.left.val}, right:{cur.right.val}')
        return result

    def preorder_traverse(self):
        if self.root is not None:
            self.__preorder(self.root)

    def __preorder(self, cur):
        self.preorder_list.append(cur.val)
        if cur.left is not None:
            self.__preorder(cur.left)
        if cur.right is not None:
            self.__preorder(cur.right)

    def inorder_traverse(self):
        if self.root is not None:
            self.__inorder(self.root)

    def __inorder(self, cur):
        if cur.left is not None:
            self.__inorder(cur.left)

        self.inorder_list.append(cur.val)

        if cur.right is not None:
            self.__inorder(cur.right)

    def postorder_traverse(self):
        if self.root is not None:
            self.__postorder(self.root)

    def __postorder(self, cur):
        if cur.left is not None:
            self.__postorder(cur.left)

        if cur.right is not None:
            self.__postorder(cur.right)

        self.postorder_list.append(cur.val)


avl = AVLtree(23)
input = [78, 11, 56, 90, 6, 88, 62, 37, 45, 98]

for i in input:
    avl.insert(i)

print(f'root: {avl.root.val}, path: {avl.traverse()}')

print("Preorder")
avl.preorder_traverse()
print(avl.preorder_list)

print("Inorder")
avl.inorder_traverse()
print(avl.inorder_list)

print("Postorder")
avl.postorder_traverse()
print(avl.postorder_list)
