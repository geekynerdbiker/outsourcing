class Patent:
    def __init__(self):
        self.data = {}

    def add_data(self, k, v):
        self.data[k] = v

    def search(self, key, value):
        if key in self.data:
            if self.data[key] == value:
                return self
        return None

    def search_by_keyword(self, keyword):
        for string in self.data['string']:
            if keyword in string:
                return self
        return None

    def print_application_number(self):
        print(self.data['applicationNumber'])

    def print_data(self):
        pass


def print_menu():
    print('1. 출원인 검색')
    print('2. 키워드 검색')
    print('3. 발명자 검색')
    print('0. 종료')
    print('>> ', end='')
    return int(input())


f = open('개인과제data.txt', 'r')
lines = f.readlines()

patents = []
attr = ['applicantName', 'openDate', 'openNumber', 'publicationNumber', 'publishDate', 'registerDate', 'registerNumber',
        'registerStatus', 'applicationDate', 'applicationNumber', 'astrtCont', 'bigDrawing', 'drawing', 'indexNo',
        'inventionTitle', 'ipcNumberdocsStarttotalSearchCount', 'name']

for line in lines:
    patent = Patent()
    ls = line.replace('<', '').split('>')

    for i in range(len(ls)):
        for a in attr:
            if a in ls[i]:
                if ls[i + 1][:6] != 'ax2102' and ls[i + 1][:7] != '/ax2102':
                    value = ls[i + 1].split('/ax2102')
                    patent.add_data(a, value[0].strip())
        patent.add_data('string', ls)
    patents.append(patent)

while True:
    selection = print_menu()

    if selection == 1:
        print()
        print('[ 출원인 검색] ')
        print('이름: ', end='')
        name = input()

        rst = []
        for p in patents:
            search_result = p.search('applicantName', name)
            if search_result:
                rst.append(search_result)

        print('\n [ 출원번호 목록 ]')
        index = 1
        for r in rst:
            print(str(index) + ": ", end='')
            r.print_application_number()
            index += 1
        print()

    elif selection == 2:
        print()
        print('[ 키워드 검색] ')
        print('키워드: ', end='')
        keyword = input()

        rst = []
        for p in patents:
            search_result = p.search_by_keyword(keyword)
            if search_result:
                rst.append(search_result)

        print('\n [ 출원번호 목록 ]')
        index = 1
        for r in rst:
            print(str(index) + ": ", end='')
            r.print_application_number()
            index += 1
        print()

    elif selection == 3:
        print()
        print('[ 발명자 검색 ] ')
        print('발명자: ', end='')
        inventor = input()

        rst = []
        for p in patents:
            search_result = p.search('name', inventor)
            if search_result:
                rst.append(search_result)

        print('\n [ 출원번호 목록 ]')
        index = 1
        for r in rst:
            print(str(index) + ": ", end='')
            r.print_application_number()
            index += 1
        print()

    elif selection == 0:
        print('프로그램을 종료합니다.')
        break
