import tkinter as tk
import os
from os import path

locations = ['북문', '쪽문', '정문', '동문']
menus = ['일식', '양식', '한식', '중식']


def result(p1, p2, p3):
    l, m = locations[p1.get() - 1], menus[p2.get() - 1]

    p = '식당/' + l + '/' + m + '/' + l + '_' + m + '_' + p3.get() + '.txt'
    if not os.path.exists(p):
        panel2 = tk.Tk()
        panel2.geometry('300x500+100+100')
        panel2.resizable(False, False)

        result_lable = tk.Label(panel2, text='식당이 존재하지 않습니다.')
        result_lable.pack()

    f = open(p, 'r')

    lines = []
    line = None
    while line != '':
        line = f.readline()
        lines.append(line.replace('\n', ''))

    panel2 = tk.Tk()
    panel2.title('Result')
    panel2.geometry('300x500+100+100')
    panel2.resizable(False, False)


    result = ''

    for l in lines:
        result += l + '\n'
    result_lable = tk.Label(panel2, text=result)
    result_lable.pack()


panel = tk.Tk()
panel.title('Food')
panel.geometry('300x500+100+100')
panel.resizable(False, False)

location_lable = tk.Label(panel, text="위치 선택")
location_lable.pack()

location_var = tk.IntVar()

index = 1
for l in locations:
    location = tk.Radiobutton(panel, text=l, value=index, variable=location_var)
    location.pack()
    index += 1

menu_lable = tk.Label(panel, text="\n\n메뉴 선택")
menu_lable.pack()

menu_var = tk.IntVar()

index = 1
for m in menus:
    menu = tk.Radiobutton(panel, text=m, value=index, variable=menu_var)
    menu.pack()
    index += 1

input_lable = tk.Label(panel, text="\n\n식당 이름 입력")
input_lable.pack()

restaurant = tk.Entry()
restaurant.pack()

confirm = tk.Button(panel, text="확인", command=lambda: result(location_var, menu_var, restaurant))
confirm.pack()

panel.mainloop()

# selection = '식당/' + location + '/' + menu
#
# restaurants = []
# restaurant_file_pathes = []
# if path.exists(selection):
#     for (root, directories, files) in os.walk(selection):
#         for file in files:
#             file_path = os.path.join(root, file)
#             strings = os.path.splitext(file_path)[0].split('_')
#             restaurants.append(strings[-1])
#             restaurant_file_pathes.append(file_path)
# else:
#     print('해당 위치의 해당 메뉴의 식당이 존재하지 않습니다.')
#
# restaurant = input('식당의 이름을 입력하세요: ')
#
# while restaurant not in restaurants:
#     print('해당 식당은 선택하신 위치와 메뉴의 식당 리스트 내에 존재하지 않습니다.')
#     location = input('식당의 이름을 입력하세요: ')
#
# index = 0
# for rstr in restaurants:
#     if rstr == restaurant:
#         break
#     else:
#         index += 1
#
# f = open(restaurant_file_pathes[index], 'r')
#
# line = None
# while line != ' ':
#     line = f.readline()
#     print(line)
