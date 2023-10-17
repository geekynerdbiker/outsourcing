class Student:
    def __init__(self, st_no, name):
        self.st_no = st_no
        self.name = name


class Course:
    def __init__(self):
        self.st_list = []

    def register(self, st_no, name):
        self.st_list.append(Student(st_no, name))
        self.st_list.sort(key=lambda x: x.st_no)

    def withdraw(self, st_no):
        for s in self.st_list:
            if s.st_no == st_no:
                self.st_list.remove(s)
                return

    def print_info(self, st_no):
        for s in self.st_list:
            if s.st_no == st_no:
                print(s.st_no + " " + s.name)

    def print_all(self):
        print(len(self.st_list))
        for s in self.st_list:
            print(s.st_no + " " + s.name)


c = Course()
while True:
    command = input().split()
    if command[0] == 'N':
        c.register(command[1], command[2])
    elif command[0] == 'C':
        c.withdraw(command[1])
    elif command[0] == 'R':
        c.print_info(command[1])
    elif command[0] == 'P':
        c.print_all()
    elif command[0] == 'Q':
        exit(0)

'''
N 1113 kim
N 1112 lee
N 1111 choi
N 1115 kim
C 1112
P
R 1113
N 1112 han
P
Q
'''