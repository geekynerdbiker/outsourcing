import json


class Lecture:
    def __init__(self, blocks_url, effort, end, enrollment_start, enrollment_end, id, course_image, name, number, org,
                 short_description, start, start_display, start_type, pacing, mobile_available, hidden):
        self.blocks_url = blocks_url  # 강좌 URL
        self.effort = effort  # 강좌 주요시간
        self.end = end  # 강좌 종료일
        self.enrollment_start = enrollment_start  # 수강신청 시작일
        self.enrollment_end = enrollment_end  # 수강신청 종료일
        self.id = id  # 강좌 이이디
        self.course_image = course_image  # 강좌 이미지
        self.name = name  # 강좌명
        self.number = number  # 강좌번호
        self.org = org  # 기관명
        self.short_description = short_description  # 짧은소개
        self.start = start  # 강좌 시작일
        self.start_display = start_display  # 강좌 시작일 표시 문구
        self.start_type = start_type  # 강좌 시작일 표시 형식
        self.pacing = pacing  # 강좌 형식
        self.mobile_available = mobile_available  # 모바일 지원여부
        self.hidden = hidden  # 강좌 감춤여부
        self.next = None

    def print(self):
        print(self.name + " " + self.blocks_url)


class IMDF:
    def __init__(self):
        self.head = None
        self.tail = None

    def store_lectures_from_json(self, filename):
        with open(filename, 'r') as f:
            data = json.load(f)

        for i in range(len(data)):
            if self.head is None:
                self.head = Lecture(data[i]['blocks_url'], data[i]['effort'], data[i]['end'],
                                    data[i]['enrollment_start'], data[i]['enrollment_end'],
                                    data[i]['id'], data[i]['media']['course_image'], data[i]['name'], data[i]['number'],
                                    data[i]['org'],
                                    data[i]['short_description'], data[i]['start'], data[i]['start_display'],
                                    data[i]['start_type'], data[i]['pacing'],
                                    data[i]['mobile_available'], data[i]['hidden'])
                self.tail = self.head
            else:
                self.tail.next = Lecture(data[i]['blocks_url'], data[i]['effort'], data[i]['end'],
                                         data[i]['enrollment_start'], data[i]['enrollment_end'],
                                         data[i]['id'], data[i]['media']['course_image'], data[i]['name'],
                                         data[i]['number'],
                                         data[i]['org'],
                                         data[i]['short_description'], data[i]['start'], data[i]['start_display'],
                                         data[i]['start_type'], data[i]['pacing'],
                                         data[i]['mobile_available'], data[i]['hidden'])
                self.tail = self.tail.next


class LDM:
    def __init__(self, IMDF):
        self.IMDF = IMDF

    def insert(self):
        return

    def search(self, attribute, target):
        attrs = ['강좌 URL', '강좌 주요시간', '강좌 종료일', '수강신청 시작일', '수강신청 종료일', '강좌 이이디', '강좌 이미지', '강좌명', '강좌번호', '기관명',
                 '짧은소개', '강좌 시작일', '강좌 시작일 표시 문구', '강좌 시작일 표시 형식', '강좌 형식', '모바일 지원여부', '강좌 감춤여부']

        if attribute not in attrs:
            print('존재하지 않는 속성입니다.')
            return

        ptr = self.IMDF.head
        while ptr is not None:
            if attribute == '강좌 URL':
                if ptr.blocks_url == target:
                    ptr.print()
            elif attribute == '강좌 주요시간':
                if ptr.effort == target:
                    ptr.print()
            elif attribute == '강좌 종료일':
                if ptr.end == target:
                    ptr.print()
            elif attribute == '수강신청 시작일':
                if ptr.enrollment_start == target:
                    ptr.print()
            elif attribute == '수강신청 종료일':
                if ptr.enrollment_end == target:
                    ptr.print()
            elif attribute == '강좌 이이디':
                if ptr.id == target:
                    ptr.print()
            elif attribute == '강좌 이미지':
                if ptr.course_image == target:
                    ptr.print()
            elif attribute == '강좌명':
                if ptr.name == target:
                    ptr.print()
            elif attribute == '강좌번호':
                if ptr.number == target:
                    ptr.print()
            elif attribute == '기관명':
                if ptr.prg == target:
                    ptr.print()
            elif attribute == '짧은소개':
                if ptr.short_description == target:
                    ptr.print()
            elif attribute == '강좌 주요시간':
                if ptr.start_type == target:
                    ptr.print()
            elif attribute == '강좌 시작일':
                if ptr.start == target:
                    ptr.print()
            elif attribute == '강좌 시작일 표시 문구':
                if ptr.start_display == target:
                    ptr.print()
            elif attribute == '강좌 시작일 표시 형식':
                if ptr.start_type == target:
                    ptr.print()
            elif attribute == '강좌 형식':
                if ptr.pacing == target:
                    ptr.print()
            elif attribute == '모바일 지원여부':
                if ptr.mobild_available == target:
                    ptr.print()
            elif attribute == '강좌 감춤여부':
                if ptr.hidden == target:
                    ptr.print()
            ptr = ptr.next


    def remove(self, name):
        ptr = self.IMDF.head
        ptr2 = None

        while ptr is not None and ptr.next is not None:
            if ptr.name == name:
                if ptr2 is None:
                    self.IMDF.head = ptr.next
                    ptr = ptr.next
                else:
                    ptr2.next = ptr.next
                    ptr = ptr.next
            ptr2 = ptr
            ptr = ptr.next


class LR:
    def __init__(self):
        pass


class PM:
    def __init__(self):
        pass


class OCP:
    def __init__(self):
        self.IMDF = IMDF()
        self.LDM = LDM(self.IMDF)
        self.LR = LR()
        self.PM = PM()

    def loads(self, filename):
        self.IMDF.store_lectures_from_json(filename)

    def search(self, attribute, target):
        self.LDM.search(attribute, target)

    def delete(self, target):
        self.LDM.remove(target)


ocp = OCP()
ocp.loads('lectures.json')
ocp.search('강좌명', '정보통신 보안')
ocp.delete('정보통신 보안')
ocp.search('강좌명', '정보통신 보안')
