# csv 파일을 읽어오는 함수
def readFiles():
    # 파일로부터 불러온 강의와 학생을 저장할 변수
    l, s = [], []

    # 강의 파일을 열어서 각 강의를 하나의 클래스로 초기화하여 리스트에 저장
    with open('lecture.csv', 'r') as f:
        next(f)
        for line in f:
            line = line.replace('\n', '').split(',')
            l.append(Lecture(line[0], int(line[1])))

    # 학생 파일을 열어서 각 학생을 하나의 클래스로 초기화하여 리스트에 저장
    with open('student.csv', 'r') as f:
        next(f)
        for line in f:
            line = line.replace('\n', '').split(',')
            s.append(Student(line[0], line[1], line[2],
                             [int(line[3]), int(line[4]), int(line[5]), int(line[6]), int(line[7])]))

    # 강의 및 학생 리스트 반환
    return l, s


# 최종적으로 수강을 확정하는 함수
def confirm(l, s):
    # 강의 리스트로부터 강의를 가리킬 인덱스
    ind = 0

    # 각각의 강의에 대해서
    for lecture in l:
        # 학생의 해당 강의 마일리지 순으로 학생리스트를 내림차순 정렬
        s.sort(key=lambda student: student.lectures[ind], reverse=True)
        # 해당 강의의 수용인원만큼 마일리지가 높은순으로 한명씩 저장
        for i in range(lecture.capacity):
            # 학생의 현재 수강 강의 갯수가 3개 미만이면 추가
            if s[i].count < 3:
                lecture.addStud(s[i])
                s[i].count += 1
            else:
                continue
        # 저장이 끝나면 인덱스 증가
        ind += 1

    # 강의 및 학생 리스트 반환
    return l, s

# 강의 클래스
class Lecture:
    # 강의 이름, 수용인원, 수강 학생들을 저장할 리스트로 클래스 초기화
    def __init__(self, id, capacity):
        self.id = id
        self.capacity = capacity
        self.students = []
        pass

    # 수강 학생을 추가하는 함수
    def addStud(self, student):
        self.students.append(student)

    # 마일리지 순으로 수강학생 정렬 함수
    def sortStud(self, i):
        self.students.sort(key=lambda student: student.lectures[i])

    # 결고 출력 함수
    def showRes(self):
        s = ''
        s += self.id + ':'
        for student in self.students:
            s += ' ' + student.id + ' /'

        print(s[:len(s) - 1])


# 학생 클래스
class Student:
    # 수강신청 순서, 학번, 학년, 각 강의에 부여된 마일리지 정보, 최대 수강 강좌 갯수, 마일리지 초기화
    def __init__(self, order, id, grade, lectures):
        self.order = order
        self.id = id
        self.grade = grade
        self.lectures = lectures

        self.count = 0
        self.mileage = 0
        pass

    # 마일리지 사용 함수
    def useMile(self):
        # 강의 이름과 사용할 마일리지를 입력받음. 마일리지의 경우 음수도 입력이 가능. 음수의 경우, 절댓값만큼 마일리지 차감
        lec = int(ord(input('Input lecture name: ')) - 65)
        mile = int(input('Input mileage to use: '))

        # 강의가 존재하지 않을 경우
        if lec < 0 or lec >= len(self.lectures):
            print('No lecture exist.')
        else:
            # 남은 마일리지가 충분하지 않을 경우
            if self.mileage < mile:
                print('Not enough mileage.')
            # 해당 강의에 입력한 만큼 마일리지 부여 및 가용 마일리지 차감
            else:
                self.lectures[lec] += mile
                self.mileage -= mile
                print('Used successfully.')

    # 수강취소 함수
    def withdraw(self):
        lec = int(input('Input lecture name: ') - 'A')

        # 강의가 존재하지 않는 경우
        if lec < 0 or lec >= len(self.lectures):
            print('No lecture exist.')
        else:
            # 해당 강의에 부여된 마일리지가 없는 경우
            if self.lectures[lec] <= 0:
                print('Already withdrawn.')
            # 강의 취소 후 해당 마일리지만큼 가용 마일리지 증가
            else:
                self.mileage += self.lectures[lec]
                self.lectures[int(lec)] = 0
                print('Withdraw successfully.')


# 파일을 읽어서 각각 강의와 학생 리스트로 저장
lectures, students = readFiles()

# 상황 연출. 학번이 20211322인 학생을 찾는다.
s = None
for student in students:
    if student.id == '20211322':
        s = student

# 콘솔의 입력을 통해 B, -2를 입력하여 차감
s.useMile()
# 콘솔의 입력을 통해 A, 2를 입력하여 부여
s.useMile()
# 변동사항 적용
lectures, students = confirm(lectures, students)

# 각 강의별로 결과 출력력
for lecture in lectures:
    lecture.showRes()
