class Student:
    def __init__(self, st_no, name, dept, grade):
        self.st_no = st_no
        self.name = name
        self.dept = dept
        self.grade = grade
        self.score = None

    def print_info(self):
        if self.score:
            print(self.st_no + " " + self.name + " " + self.dept + " " + self.grade + " " + self.score)
        else:
            print(self.st_no + " " + self.name + " " + self.dept + " " + self.grade)


class Node():
    def __init__(self, data):
        self.data = data
        self.left = self.right = None


class Course:
    def __init__(self):
        self.root = None
        self.students = []

    def search(self, st_no):
        curr = self.root

        while curr:
            if curr.data.st_no == st_no:
                return curr
            elif st_no < curr.data.st_no:
                curr = curr.left
            else:
                curr = curr.right
        return curr

    def register(self, st_no, name, dept, grade):  # N
        n = Node(Student(st_no, name, dept, grade))

        curr = self.root

        if curr is None:
            self.root = n
            return True

        while True:
            parent = curr
            if st_no == curr.data.st_no:
                print("error1")
                return False
            elif st_no < curr.data.st_no:
                curr = curr.left
                if not curr:
                    parent.left = n
                    return True
            else:
                curr = curr.right
                if not curr:
                    parent.right = n
                    return True

    def edit(self, st_no, score):  # G
        node = self.search(st_no)

        if node:
            node.data.score = score
        else:
            print("error2")

    def withdraw(self, st_no):  # C
        self.root, n = self._remove_rec(self.root, st_no)
        if n is not None:
            n.left = n.right = None
        return n

    def _remove_rec(self, curr, st_no):
        if curr is None:
            return None, None

        elif st_no < curr.data.st_no:
            curr.left, n = self._remove_rec(curr.left, st_no)
        elif st_no > curr.data.st_no:
            curr.right, n = self._remove_rec(curr.right, st_no)
        else:
            if not curr.left and not curr.right:
                n = curr
                curr = None
            elif not curr.right:
                n = curr
                curr = curr.left
            elif not curr.left:
                n = curr
                curr = curr.right
            else:
                rep = curr.left
                while rep.right:
                    rep = rep.right
                curr.data, rep.data = rep.data, curr.data
                curr.left, n = self._remove_rec(curr.left, rep.data.st_no)

        return curr, n

    def inquire(self, st_no):  # R
        node = self.search(st_no)

        if node:
            node.data.print_info()
        else:
            print("error2")

    def inquire_dept(self, dept):
        while self.curr:
            if self.curr.value.dept == dept:
                searched = True
                break
            elif dept < self.curr.value.dept:
                self.parent = self.curr
                self.curent_node = self.curr.left
            else:
                self.parent = self.curr
                self.curr = self.curr.right

    def preorder(self, curr):
        if not curr:
            return
        self.preorder(curr.left)
        if not self.students.__contains__(curr.data):
            self.students.append(curr.data)
        self.preorder(curr.right)

    def print_all(self):  # P
        self.students = []
        self.preorder(self.root)
        for s in self.students:
            s.print_info()

    def print_dept(self, dept):
        count = 0
        self.students = []
        self.preorder(self.root)

        for s in self.students:
            if s.dept == dept:
                count += 1

        print(count)
        for s in self.students:
            if s.dept == dept:
                s.print_info()


c = Course()
count = 0
while True:
    command = input().split()
    if command[0] == 'N':
        if c.register(command[1], command[2], command[3], command[4]):
            count += 1
    elif command[0] == 'G':
        c.edit(command[1], command[2])
    elif command[0] == 'C':
        if c.withdraw(command[1]):
            count -= 1
        else:
            print("error2")
    elif command[0] == 'R':
        c.inquire(command[1])
    elif command[0] == 'P':
        print(count)
        c.print_all()
    elif command[0] == 'D':
        c.print_dept(command[1])

    elif command[0] == 'Q':
        exit(0)
'''
N 1112 kim ces 3
N 1113 kim ces 2
N 1111 lee ces 2
N 1115 kim ee 2
N 1112 choi ces 3
R 1111
C 1112
C 1116
P
N 1110 yoon ces 3
P
D ces
G 1110 A+
G 1111 A0
G 1112 B+
G 1115 A0
G 1113 B0
R 1113
P
Q
'''
