import os
import xlsxwriter
from win32com import client


class Node:
    def __init__(self, name=None, module_name=None, description=None, activity_dates=None, scheduled_days=None,
                 scheduled_start_time=None,
                 scheduled_end_time=None, duration=None, allocated_location_name=None, planned_size=None,
                 allocated_staff_name=None, zone_name=None):
        self.name = name
        self.module_name = module_name
        self.description = description
        self.activity_dates = activity_dates
        self.scheduled_days = scheduled_days
        self.scheduled_start_time = scheduled_start_time
        self.scheduled_end_time = scheduled_end_time
        self.duration = duration
        self.allocated_location_name = allocated_location_name
        self.planned_size = planned_size
        self.allocated_staff_name = allocated_staff_name
        self.zone_name = zone_name
        self.next = None

    def copy(self):
        return Node(self.name, self.module_name, self.description, self.activity_dates, self.scheduled_days,
                    self.scheduled_start_time, self.scheduled_end_time, self.duration, self.allocated_location_name,
                    self.planned_size, self.allocated_staff_name, self.zone_name)

    def print(self):
        s = "%-20s %-10s %-10s %-10s %-10s %-10s %-20s %-5s %-20s %-10s" % (
            self.name, self.activity_dates, self.scheduled_days, self.scheduled_start_time, self.scheduled_end_time,
            self.duration, self.allocated_location_name, self.planned_size, self.allocated_staff_name, self.zone_name)
        print(s)


class LinkedList:
    def __init__(self):
        self.head = None
        self.length = 0

    def add(self, data):
        if self.head is None:
            self.head = data
            self.length += 1
            return

        curr = self.head

        while curr.next:
            curr = curr.next
        curr.next = data
        self.length += 1

    def copy(self):
        ll = LinkedList()
        curr = self.head

        while curr:
            ll.add(curr.copy())
            curr = curr.next

        return ll

    def compare_date(self, s1, s2):
        d1 = s1.split('/')
        d2 = s2.split('/')

        if int(d1[2]) < int(d2[2]):
            return True
        elif int(d1[2]) == int(d2[2]):
            if int(d1[1]) < int(d2[1]):
                return True
            elif int(d1[1]) == int(d2[1]):
                if int(d1[0]) < int(d2[0]):
                    return True
        return False

    def compare_day(self, s1, s2):
        days = {'Monday': 0, 'Tuesday': 1, 'Wednesday': 2, 'Thursday': 3, 'Friday': 4, 'Saturday': 5, 'Sunday': 6}
        d1 = days[s1]
        d2 = days[s2]

        return d1 < d2

    def compare_time(self, s1, s2):
        t1 = s1.split(':')
        t2 = s2.split(':')

        if int(t1[0]) < int(t2[0]):
            return True
        elif int(t1[0]) == int(t2[0]):
            if int(t1[1]) < int(t2[1]):
                return True
            elif int(t1[1]) == int(t2[1]):
                if int(t1[2]) < int(t2[2]):
                    return True
        return False

    def compare_duration(self, s1, s2):
        t1 = s1.split(':')
        t2 = s2.split(':')

        if int(t1[0]) < int(t2[0]):
            return True
        elif int(t1[0]) == int(t2[0]):
            if int(t1[1]) < int(t2[1]):
                return True
        return False

    def insert(self, head, node, order, category):
        dummy = Node()
        curr = dummy
        dummy.next = head

        while True:
            if order == 1:
                if category == 1:
                    if curr.next and curr.next.name < node.name:
                        curr = curr.next
                    else:
                        break
                elif category == 2:
                    if curr.next and self.compare_date(curr.next.activity_dates, node.activity_dates):
                        curr = curr.next
                    else:
                        break
                elif category == 3:
                    if curr.next and self.compare_day(curr.next.scheduled_days, node.scheduled_days):
                        curr = curr.next
                    else:
                        break
                elif category == 4:
                    if curr.next and self.compare_time(curr.next.scheduled_start_time, node.scheduled_start_time):
                        curr = curr.next
                    else:
                        break
                elif category == 5:
                    if curr.next and self.compare_time(curr.next.scheduled_end_time, node.scheduled_end_time):
                        curr = curr.next
                    else:
                        break
                elif category == 6:
                    if curr.next and self.compare_duration(curr.next.duration, node.duration):
                        curr = curr.next
                    else:
                        break
                elif category == 7:
                    if curr.next and curr.next.allocated_location_name < node.allocated_location_name:
                        curr = curr.next
                    else:
                        break
                elif category == 8:
                    if curr.next and curr.next.planned_size < node.planned_size:
                        curr = curr.next
                    else:
                        break
                elif category == 9:
                    if curr.next and curr.next.allocated_staff_name < node.allocated_staff_name:
                        curr = curr.next
                    else:
                        break
                elif category == 10:
                    if curr.next and curr.next.zone_name < node.zone_name:
                        curr = curr.next
                    else:
                        break

            else:
                if category == 1:
                    if curr.next and curr.next.name > node.name:
                        curr = curr.next
                    else:
                        break
                elif category == 2:
                    if curr.next and self.compare_date(node.activity_dates, curr.next.activity_dates):
                        curr = curr.next
                    else:
                        break
                elif category == 3:
                    if curr.next and self.compare_day(node.scheduled_days, curr.next.scheduled_days):
                        curr = curr.next
                    else:
                        break
                elif category == 4:
                    if curr.next and self.compare_time(node.scheduled_start_time, curr.next.scheduled_start_time):
                        curr = curr.next
                    else:
                        break
                elif category == 5:
                    if curr.next and self.compare_time(node.scheduled_end_time, curr.next.scheduled_end_time):
                        curr = curr.next
                    else:
                        break
                elif category == 6:
                    if curr.next and self.compare_duration(node.duration, curr.next.duration):
                        curr = curr.next
                    else:
                        break
                elif category == 7:
                    if curr.next and curr.next.allocated_location_name > node.allocated_location_name:
                        curr = curr.next
                    else:
                        break
                elif category == 8:
                    if curr.next and curr.next.planned_size > node.planned_size:
                        curr = curr.next
                    else:
                        break
                elif category == 9:
                    if curr.next and curr.next.allocated_staff_name > node.allocated_staff_name:
                        curr = curr.next
                    else:
                        break
                elif category == 10:
                    if curr.next and curr.next.zone_name > node.zone_name:
                        curr = curr.next
                    else:
                        break

        node.next = curr.next
        curr.next = node
        return dummy.next

    def sort(self, order, category):
        result = None
        curr = self.head

        while curr:
            next = curr.next
            result = self.insert(result, curr, order, category)
            curr = next

        return result

    def get(self, date, time):
        result = None
        curr = self.head

        def compare_time_and_date(n, d, t):
            d1 = n.activity_dates.split('/')
            t1 = n.scheduled_start_time.split(':')

            return int(d1[0]) == d[0] and int(d1[1]) == d[1] and int(d1[2]) == d[2] and int(t1[0]) == t[0] and int(
                t1[1]) == t[1]

        while curr:
            if compare_time_and_date(curr, date, time):
                result = curr
                break
            curr = curr.next

        if result is not None:
            name = result.name.split('_')
            result = name[1] + '\n' + name[2]
            return result
        return '\n\n\n'

    def find(self, category, keyword):
        nl = LinkedList()
        curr = self.head

        while curr:
            if category == 1:
                if keyword == curr.name:
                    nl.add(curr.copy())
            elif category == 2:
                if keyword == curr.activity_dates:
                    nl.add(curr.copy())
            elif category == 3:
                if keyword == curr.scheduled_days:
                    nl.add(curr.copy())
            elif category == 4:
                if keyword == curr.scheduled_start_time:
                    nl.add(curr.copy())
            elif category == 5:
                if keyword == curr.scheduled_end_time:
                    nl.add(curr.copy())
            elif category == 6:
                if keyword == curr.duration:
                    nl.add(curr.copy())
            elif category == 7:
                if keyword == curr.allocated_location_name:
                    nl.add(curr.copy())
            elif category == 8:
                if keyword == curr.planned_size:
                    nl.add(curr.copy())
            elif category == 9:
                if keyword == curr.allocated_staff_name:
                    nl.add(curr.copy())
            elif category == 10:
                if keyword == curr.zone_name:
                    nl.add(curr.copy())
            curr = curr.next

        return nl

    def print(self):
        s = "%-20s %-10s %-10s %-10s %-10s %-10s %-20s %-5s %-20s %-10s" % (
            'Name', 'Date', 'Day', 'Start', 'End', 'Duration', 'Location', 'Size', 'Staff', 'Zone')
        print(s)
        h = self.head
        while h:
            h.print()
            h = h.next


ll = LinkedList()
path = input('$ Path: ')
file_list = os.listdir(path)

print('File list in path')
for i in range(len(file_list)):
    print(str(i + 1) + ': ' + file_list[i])

selected = input('$ Select files:').split(' ')
new_list = []

for i in selected:
    new_list.append(file_list[int(i) - 1])

for file in new_list:
    if file.__contains__('csv'):
        with open(path + '/' + file, 'r') as f:
            results = []
            for line in f:
                words = line.split(',')
                results.append(words)

                if "unchecked" in (words[4] or words[5] or words[6]):
                    continue
                if "Name" in words[1]:
                    continue
                ll.add(
                    Node(words[1].replace("DICT-DNDFC_221_", ""),
                         words[1].replace("DICT-DNDFC_221_FT_", "").split('_')[0], words[2], words[3], words[4],
                         words[5], words[6], words[7], words[8], words[9],
                         words[10], words[11].replace("\n", "")))

rst = ll.copy()

while True:
    inp = int(input('1: Sort\n2: Print\n3: Export\n4: Quit\n\n$ '))

    if inp == 1:
        query = int(input(
            'Search by\n1: Name\n2: Date\n3: Day\n4: Start\n5: End\n6: Duration\n7: Location\n8: Size\n9: Staff\n10: '
            'Zone\n\n$ '))
        keyword = input('$ Input keyword: ')

        category = int(input(
            'Sort by\n1: Name\n2: Date\n3: Day\n4: Start\n5: End\n6: Duration\n7: Location\n8: Size\n9: Staff\n10: '
            'Zone\n\n$ '))
        order = int(input('Order by\n1: ASC\n2: DESC\n\n$ '))
        rst.head = ll.find(query, keyword).sort(order, category)
        rst.print()
    elif inp == 2:
        ll.print()
    elif inp == 3:
        wb = xlsxwriter.Workbook(path + 'Timetable.xlsx')
        ws = wb.add_worksheet('table')

        f1 = wb.add_format({'bold': True, 'align': 'center', 'border': True, 'bg_color': 'yellow'})
        f2 = wb.add_format({'align': 'center', 'border': True, 'bg_color': 'yellow'})

        ws.merge_range('A1:A2', 'Week', f1)

        ws.merge_range('B1:G1', 'MON', f1)
        ws.merge_range('B2:C2', '8:30-11:30', f2)
        ws.merge_range('D2:E2', '12:00-15:00', f2)
        ws.merge_range('F2:G2', '15:30-18:30', f2)

        ws.merge_range('H1:M1', 'TUE', f1)
        ws.merge_range('H2:I2', '8:30-11:30', f2)
        ws.merge_range('J2:K2', '12:00-15:00', f2)
        ws.merge_range('L2:M2', '15:30-18:30', f2)

        ws.merge_range('N1:S1', 'WED', f1)
        ws.merge_range('N2:O2', '8:30-11:30', f2)
        ws.merge_range('P2:Q2', '12:00-15:00', f2)
        ws.merge_range('R2:S2', '15:30-18:30', f2)

        ws.merge_range('T1:Y1', 'THU', f1)
        ws.merge_range('T2:U2', '8:30-11:30', f2)
        ws.merge_range('V2:W2', '12:00-15:00', f2)
        ws.merge_range('X2:Y2', '15:30-18:30', f2)

        ws.merge_range('Z1:AE1', 'FRI', f1)
        ws.merge_range('Z2:AA2', '8:30-11:30', f2)
        ws.merge_range('AB2:AC2', '12:00-15:00', f2)
        ws.merge_range('AD2:AE2', '15:30-18:30', f2)

        idx = 1
        start, end = 3, 7

        yy, mm, dd = 2021, 4, 5
        month = {4: 'April', 5: 'May', 6: 'June'}
        f3 = wb.add_format({'align': 'center', 'border': True, 'bg_color': 'orange'})

        IP = wb.add_format({'align': 'center', 'border': True, 'bg_color': 'green'})
        DCNG = wb.add_format({'align': 'center', 'border': True, 'bg_color': 'blue'})
        ISOG = wb.add_format({'align': 'center', 'border': True, 'bg_color': 'red'})
        DM = f4 = wb.add_format({'align': 'center', 'border': True, 'bg_color': 'pink'})
        NONE = wb.add_format({'align': 'center', 'border': True, 'bg_color': 'white'})

        format_dict = {'IP': IP, 'DCNG': DCNG, 'ISOG': ISOG, 'DM': DM, 'NONE': NONE}


        def day_adder(d, m):
            if m == 4 and d == 30:
                m += 1
                d = 1
            elif m == 5 and d == 31:
                m += 1
                d = 1
            else:
                d += 1
            return d, m


        while idx <= 10:
            ws.merge_range('A' + str(start) + ':A' + str(end), idx, f1)

            ws.merge_range('B' + str(start) + ':G' + str(start),
                           'Monday' + ' ' + str(dd) + ' ' + month[mm] + ' ' + str(yy),
                           f3)

            data = rst.get([dd, mm, yy], [8, 30])
            if len(data) < 5:
                fm = format_dict['NONE']
            else:
                fm = format_dict[data.split('\n')[0]]
            ws.merge_range('B' + str(start + 1) + ':C' + str(end), data, fm)

            data = rst.get([dd, mm, yy], [12, 00])
            if len(data) < 5:
                fm = format_dict['NONE']
            else:
                fm = format_dict[data.split('\n')[0]]
            ws.merge_range('D' + str(start + 1) + ':E' + str(end), data, fm)

            data = rst.get([dd, mm, yy], [15, 30])
            if len(data) < 5:
                fm = format_dict['NONE']
            else:
                fm = format_dict[data.split('\n')[0]]
            ws.merge_range('F' + str(start + 1) + ':G' + str(end), data, fm)
            dd, mm = day_adder(dd, mm)

            ws.merge_range('H' + str(start) + ':M' + str(start),
                           'Tuesday' + ' ' + str(dd) + ' ' + month[mm] + ' ' + str(yy), f3)

            data = rst.get([dd, mm, yy], [8, 30])
            if len(data) < 5:
                fm = format_dict['NONE']
            else:
                fm = format_dict[data.split('\n')[0]]
            ws.merge_range('H' + str(start + 1) + ':I' + str(end), data, fm)
            data = rst.get([dd, mm, yy], [12, 00])
            if len(data) < 5:
                fm = format_dict['NONE']
            else:
                fm = format_dict[data.split('\n')[0]]
            ws.merge_range('J' + str(start + 1) + ':K' + str(end), data, fm)
            data = rst.get([dd, mm, yy], [15, 30])
            if len(data) < 5:
                fm = format_dict['NONE']
            else:
                fm = format_dict[data.split('\n')[0]]
            ws.merge_range('L' + str(start + 1) + ':M' + str(end), data, fm)
            dd, mm = day_adder(dd, mm)

            ws.merge_range('N' + str(start) + ':S' + str(start),
                           'Wednesday' + ' ' + str(dd) + ' ' + month[mm] + ' ' + str(yy), f3)

            data = rst.get([dd, mm, yy], [8, 30])
            if len(data) < 5:
                fm = format_dict['NONE']
            else:
                fm = format_dict[data.split('\n')[0]]
            ws.merge_range('N' + str(start + 1) + ':O' + str(end), data, fm)
            data = rst.get([dd, mm, yy], [12, 00])
            if len(data) < 5:
                fm = format_dict['NONE']
            else:
                fm = format_dict[data.split('\n')[0]]
            ws.merge_range('P' + str(start + 1) + ':Q' + str(end), data, fm)
            data = rst.get([dd, mm, yy], [15, 30])
            if len(data) < 5:
                fm = format_dict['NONE']
            else:
                fm = format_dict[data.split('\n')[0]]
            ws.merge_range('R' + str(start + 1) + ':S' + str(end), data, fm)
            dd, mm = day_adder(dd, mm)

            ws.merge_range('T' + str(start) + ':Y' + str(start),
                           'Thursday' + ' ' + str(dd) + ' ' + month[mm] + ' ' + str(yy), f3)

            data = rst.get([dd, mm, yy], [8, 30])
            if len(data) < 5:
                fm = format_dict['NONE']
            else:
                fm = format_dict[data.split('\n')[0]]
            ws.merge_range('T' + str(start + 1) + ':U' + str(end), data, fm)
            data = rst.get([dd, mm, yy], [12, 00])
            if len(data) < 5:
                fm = format_dict['NONE']
            else:
                fm = format_dict[data.split('\n')[0]]
            ws.merge_range('V' + str(start + 1) + ':W' + str(end), data, fm)
            data = rst.get([dd, mm, yy], [15, 30])
            if len(data) < 5:
                fm = format_dict['NONE']
            else:
                fm = format_dict[data.split('\n')[0]]
            ws.merge_range('X' + str(start + 1) + ':Y' + str(end), data, fm)
            dd, mm = day_adder(dd, mm)

            ws.merge_range('Z' + str(start) + ':AE' + str(start),
                           'Friday' + ' ' + str(dd) + ' ' + month[mm] + ' ' + str(yy), f3)

            data = rst.get([dd, mm, yy], [8, 30])
            if len(data) < 5:
                fm = format_dict['NONE']
            else:
                fm = format_dict[data.split('\n')[0]]
            ws.merge_range('Z' + str(start + 1) + ':AA' + str(end), data, fm)
            data = rst.get([dd, mm, yy], [12, 00])
            if len(data) < 5:
                fm = format_dict['NONE']
            else:
                fm = format_dict[data.split('\n')[0]]
            ws.merge_range('AB' + str(start + 1) + ':AC' + str(end), data, fm)
            data = rst.get([dd, mm, yy], [15, 30])
            if len(data) < 5:
                fm = format_dict['NONE']
            else:
                fm = format_dict[data.split('\n')[0]]
            ws.merge_range('AD' + str(start + 1) + ':AE' + str(end), data, fm)

            dd, mm = day_adder(dd, mm)
            dd, mm = day_adder(dd, mm)
            dd, mm = day_adder(dd, mm)

            idx += 1
            start += 5
            end += 5

        wb.close()

        excel = client.Dispatch("Excel.Application")
        sheets = excel.Workbooks.Open(path + 'Timetable.xlsx')
        work_sheets = sheets.Worksheets[0]
        work_sheets.ExportAsFixedFormat(0, 'Timetable.pdf')

    elif inp == 4:
        break
    else:
        print('Wrong Command!')
