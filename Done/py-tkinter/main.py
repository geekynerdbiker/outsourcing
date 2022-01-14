from tkinter import *
from tkinter import ttk
from tkinter import messagebox
from PIL import Image, ImageTk
import os

title = '제목을 입력하세요.'

name = '김**'
snum = '123456'
univ = '이화여자대학교'
major = '간호학과'
addr = '서울시 노원구 ***'
hobby = '독서'

mbti = 'ABCD'
vol = '봉사활동: 현충원 관리, 어르신 돌보기 등'
strn = '저의 장점은 ~'
weak = '저의 단점은 ~'

root = Tk()
root.title(title)
root.resizable(False, False)

img = Image.open("user.png")
img = img.resize((220, 300), Image.ANTIALIAS)
image = ImageTk.PhotoImage(img)
imageLabel = Label(root, image=image)
imageLabel.grid(row=1, column=0, columnspan=2)

treeview = ttk.Treeview(root, columns=["one", "two"], displaycolumns=["one", "two"])
treeview.grid(row=3, column=0, columnspan=2)

treeview.column("#0", width=10)

treeview.column("#1", width=100, anchor="center")
treeview.heading("one", text="제목", anchor="center")

treeview.column("#2", width=220, anchor="center")
treeview.heading("two", text="내용", anchor="center")

# 표에 삽입될 데이터
treelist = [('이름', name), ('학번', snum), ('학교', univ), ('학과', major), ('주소', addr), ('취미', hobby)]

# 표에 데이터 삽입
for i in range(len(treelist)):
    treeview.insert('', 'end', text=i, values=treelist[i], iid=str(i) + "번")

b1 = Button(root, text='MBTI')
b2 = Button(root, text='봉사활동')
b3 = Button(root, text='장점')
b4 = Button(root, text='단점')

b1.grid(row=4, column=0)
b2.grid(row=4, column=1)
b3.grid(row=5, column=0)
b4.grid(row=5, column=1)


def b1_click(event):
    print("MBTI 버튼이 클릭되었습니다")
    messagebox.showinfo("MBTI", mbti)


def b2_click(event):
    print("봉사활동 버튼이 클릭되었습니다")
    root2 = Toplevel(root)
    root2.title('봉사활동')
    root2.resizable(False, False)

    imageTitle2 = Label(root2, text=vol)
    imageTitle2.grid(row=0, column=0, columnspan=2)

    img2 = Image.open('vol.jpg')
    image2 = ImageTk.PhotoImage(img2)
    imageLabel2 = Label(root2, image=image2)
    imageLabel2.grid(row=1, column=0, columnspan=1)

    root2.mainloop()


def b3_click(event):
    print("장점 버튼이 클릭되었습니다")
    messagebox.showinfo("장점", strn)


def b4_click(event):
    print("단점 버튼이 클릭되었습니다")
    messagebox.showinfo("단점", weak)


b1.bind('<Button-1>', b1_click)
b2.bind('<Button-1>', b2_click)
b3.bind('<Button-1>', b3_click)
b4.bind('<Button-1>', b4_click)

root.mainloop()
