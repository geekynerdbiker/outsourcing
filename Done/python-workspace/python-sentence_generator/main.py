import random

import clipboard
from tkinter import *

items = []
prev = None


def load():
    global items

    items = []
    listbox.delete(0, END)

    f = open('sentences.txt', 'r')
    if f is None:
        label_gen['text'] = '불러올 파일이 존재하지 않습니다.'
        return

    line = None
    while line != '':
        line = f.readline().strip()
        items.append(line)

    items = items[:-1]
    for s in items:
        listbox.insert(END, s)
    scrollbar.config(command=listbox.yview)


def save():
    global items
    f = open('sentences.txt', 'w')

    if len(items) == 0:
        label_gen['text'] = '저장할 항목이 없습니다.'
    for s in items:
        f.write(s + '\n')


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


def generate():
    global items, prev

    if len(items) == 0:
        label_gen['text'] = '문장을 추가하거나 파일을 불러오세요.'
        return

        return

    index = None
    while True:
        if prev is None and index is not None:
            break
        elif prev is not None and index is not None:
            if items[prev] != items[index]:
                break

        index = random.randint(0, len(items) - 1)

    prev = index
    label_gen['text'] = items[index] + ' 가 복사되었습니다.'
    clipboard.copy(items[index])


root = Tk()
# root.wm_attributes('-toolwindow', 'True')
root.title("Sentence Generator")
root.resizable(False, False)

width = root.winfo_screenwidth()
height = root.winfo_screenheight()

root.geometry("800x350+" + str((width - 1400)) + '+' + str((height - 400) // 2))

frame1 = Frame(root)
frame1.pack(pady=10)

list_frame = Frame(frame1)
list_frame.pack()

scrollbar = Scrollbar(list_frame, orient='vertical')
scrollbar.pack(side='right', fill='y')

listbox = Listbox(list_frame, width=100, selectmode='extended', yscrollcommand=scrollbar.set)
listbox.pack(side='left', fill='y')

btn_frame1 = Frame(frame1)
btn_frame1.pack(ipadx=5, pady=5)

btn_save = Button(btn_frame1, text='저장', width=15, height=2, command=save)
btn_save.pack(side='right')

btn_load = Button(btn_frame1, text='불러오기', width=15, height=2, command=load)
btn_load.pack(side='left')

frame2 = Frame(root)
frame2.pack(pady=10)

ent_add = Entry(frame2, width=100)
ent_add.insert(0, '')
ent_add.pack()

btn_frame2 = Frame(frame2)
btn_frame2.pack(pady=5)

btn_add = Button(btn_frame2, text='추가', width=15, height=2, command=insert)
btn_add.grid(row=0, column=0)

btn_del = Button(btn_frame2, text='삭제', width=15, height=2, command=delete)
btn_del.grid(row=0, column=1, padx=5)

btn_gen = Button(btn_frame2, text='생성', width=15, height=2, command=generate)
btn_gen.grid(row=0, column=2)

label_gen = Label(root, text='')
label_gen.pack()

root.mainloop()
