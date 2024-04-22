import random
import tkinter.ttk
from tkinter import *
from PIL import Image, ImageDraw, ImageFont

directions = [(0, 1), (1, 1), (1, 0), (1, -1), (0, -1), (-1, -1), (-1, 0), (-1, 1)]

items = []
korean = []

file = open('korean.txt', 'r', encoding='UTF-8')

while True:
    line = file.readline()
    for l in line:
        korean.append(l)
    if not line:
        break


def delete():
    global items
    sel = listbox.curselection()

    if len(sel) == 0:
        label_gen['text'] = '삭제할 문장을 선택하세요.'
        return

    val = listbox.get(sel[0])
    index = items.index(val)
    del items[index]
    listbox.delete(sel[0])


def insert():
    global items
    if ent_add.get() == '':
        label_gen['text'] = '추가할 문장을 입력하세요.'
        return
    items.append(ent_add.get())
    listbox.insert(END, ent_add.get())
    ent_add.delete(0, len(ent_add.get()))


def get_possibles(map, word):
    possibiles = []

    row, col = len(map), len(map[0])
    for r in range(row):
        for c in range(col):
            for d in range(len(directions)):
                if check_dir_val[d].get():
                    if len(word) + r > row:
                        if d == 1 or d == 2 or d == 3:
                            continue
                    if r - len(word) < 0:
                        if d == 5 or d == 6 or d == 7:
                            continue
                    if len(word) + c > col:
                        if d == 0 or d == 1 or d == 8:
                            continue
                    if c - len(word) < 0:
                        if d == 3 or d == 4 or d == 5:
                            continue

                    if map[r][c] != '*':
                        continue

                    curr = [r, c]
                    length = 0

                    for i in range(len(word) - 1):
                        curr[0] += directions[d][0]
                        curr[1] += directions[d][1]

                        if curr[0] < row and curr[1] < col and map[curr[0]][curr[1]] != '*':
                            break
                        length += 1

                    if length == len(word) - 1:
                        possibiles.append((r, c, d))
    return possibiles


def set_item(map, word, pos):
    r = random.randint(0, len(pos) - 1)

    curr = [pos[r][0], pos[r][1]]
    for i in range(len(word) - 1):
        map[curr[0]][curr[1]] = word[i]
        curr[0] += directions[pos[r][2]][0]
        curr[1] += directions[pos[r][2]][1]
    map[curr[0]][curr[1]] = word[len(word) - 1]


def generate():
    global items
    try:
        if not 4 <= int(cbox_col.get()) <= 7:
            label_gen['text'] = '가로 값이 올바르지 않습니다.'
            return
        if not 4 <= int(cbox_row.get()) <= 7:
            label_gen['text'] = '세로 값이 올바르지 않습니다.'
            return

    except:
        label_gen['text'] = '가로 또는 세로 값이 올바르지 않습니다.'
        return

    col = cbox_col.get()
    row = cbox_row.get()

    map = [['*' for _ in range(int(col))] for _ in range(int(row))]

    for item in items:
        pos = get_possibles(map, item)
        set_item(map, item, pos)

    for m in map:
        print(m)

    img_quiz = Image.new("RGB", (int(col) * 120, int(row) * 120), (255, 255, 255))
    d_quiz = ImageDraw.Draw(img_quiz)

    img_ans = Image.new("RGB", (int(col) * 120, int(row) * 120), (255, 255, 255))
    d_ans = ImageDraw.Draw(img_ans)

    for r in range(int(row)):
        for c in range(int(col)):
            d_ans.text((c * 120 + 15, r * 120 + 5), map[r][c], font=ImageFont.truetype("GodoM.ttf", 100),
                        fill=(0, 0, 0))
            d_ans.rectangle((c * 120, r * 120, c * 120 + 120, r * 120 + 120), outline=(150, 150, 150), width=2)

            if map[r][c] == '*':
                map[r][c] = korean[random.randint(0, len(korean)-1)]
            d_quiz.text((c * 120 + 15, r * 120 + 5), map[r][c], font=ImageFont.truetype("GodoM.ttf", 100), fill=(0, 0, 0))
            d_quiz.rectangle((c * 120, r * 120, c * 120 + 120, r * 120 + 120), outline=(150, 150, 150), width=2)

    img_quiz.save('퀴즈.jpg')
    img_ans.save('정답.jpg')

    label_gen['text'] = '퀴즈 및 정답이 생성되었습니다.'
    return

root = Tk()
# root.wm_attributes('-toolwindow', 'True')
root.title("Sentence Generator")
root.resizable(False, False)

width = root.winfo_screenwidth()
height = root.winfo_screenheight()

root.geometry("600x200+" + str((width - 1400)) + '+' + str((height - 400) // 2))

panel = Frame(root)
panel.pack()

frame1 = Frame(panel)
frame1.pack(side='left')

list_frame = Frame(frame1)
list_frame.pack(ipady=5, padx=10)

lbl_answer = Label(list_frame, text="정답 목록")
lbl_answer.pack()
listbox = Listbox(list_frame, width=15, height=4, selectmode='extended')
listbox.pack()
btn_gen = Button(list_frame, text='생성', width=15, height=2, command=generate)
btn_gen.pack(pady=5)

frame2 = Frame(panel)
frame2.pack(side='right')

cbox_frame1 = Frame(frame2)
cbox_frame1.pack(pady=10)

vals = ["4", "5", "6", "7"]
cbox_col = tkinter.ttk.Combobox(cbox_frame1, values=vals, width=8)
cbox_col.grid(row=0, column=0)
cbox_col.set("가로")
# cbox_col.set("4")

cbox_row = tkinter.ttk.Combobox(cbox_frame1, values=vals, width=8)
cbox_row.grid(row=1, column=0)
cbox_row.set("세로")
# cbox_row.set("6")

ent_add = Entry(frame2, width=16)
ent_add.insert(0, '')
ent_add.pack()

btn_frame = Frame(frame2)
btn_frame.pack(ipady=5)

btn_add = Button(btn_frame, text='추가', width=7, height=2, command=insert)
btn_add.pack(side='left')

btn_del = Button(btn_frame, text='삭제', width=7, height=2, command=delete)
btn_del.pack(side='right')

label_gen = Label(root, text='')
label_gen.pack()

frame3 = Frame(panel)
frame3.pack(pady=20)

check_dir_val = [IntVar() for _ in range(8)]

check_dir1 = Checkbutton(frame3, text='→', variable=check_dir_val[0])
check_dir2 = Checkbutton(frame3, text='↘', variable=check_dir_val[1])
check_dir3 = Checkbutton(frame3, text='↓', variable=check_dir_val[2])
check_dir4 = Checkbutton(frame3, text='↙', variable=check_dir_val[3])
check_dir5 = Checkbutton(frame3, text='←', variable=check_dir_val[4])
check_dir6 = Checkbutton(frame3, text='↖', variable=check_dir_val[5])
check_dir7 = Checkbutton(frame3, text='↑', variable=check_dir_val[6])
check_dir8 = Checkbutton(frame3, text='↗', variable=check_dir_val[7])

check_dir1.grid(row=1, column=2)
check_dir2.grid(row=2, column=2)
check_dir3.grid(row=2, column=1)
check_dir4.grid(row=2, column=0)
check_dir5.grid(row=1, column=0)
check_dir6.grid(row=0, column=0)
check_dir7.grid(row=0, column=1)
check_dir8.grid(row=0, column=2)

check_dir1.select()
check_dir2.select()
check_dir3.select()

root.mainloop()
