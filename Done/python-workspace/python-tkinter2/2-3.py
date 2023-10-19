import tkinter.messagebox  # 팝업창을 위해 임포트
from tkinter import *

window = Tk()  # 객체 생성

window.title('안드로이드')  # 타이틀 지정
window.geometry("540x360")  # 창 크기 지정


def action1():  # 에클레어 창
    newWindow = Toplevel(window)  # 최상위 프레임 지정 후 새창
    newWindow.title('에클레어')
    newWindow.geometry("320x320")

    img = PhotoImage(file='android07.gif')  # 이미지를 불러옴
    lbl = Label(newWindow, image=img)  # 이미지 라벨 생성
    btn = Button(newWindow, text='종료하기', command=ask)  # 버튼 라벨 생성

    lbl.pack()  # 배치
    btn.pack()

    newWindow.mainloop()  # 실행


def action2():
    newWindow = Toplevel(window)  # 최상위 프레임 지정 후 새창
    newWindow.title('허니콤')
    newWindow.geometry("320x320")

    menuBar = Menu(newWindow)  # 메뉴바 생성
    newWindow.config(menu=menuBar)  # 메뉴바 지정
    menu = Menu(menuBar)  # 메뉴 생성
    menu.add_command(label='하위 메뉴 1')  # 하위 메뉴 추가
    menu.add_command(label='하위 메뉴 2')
    menu.add_command(label='하위 메뉴 3', command=ask)
    menuBar.add_cascade(label='상위 메뉴')  # 상위 메뉴 추가

    img = PhotoImage(file='android08.gif')
    lbl = Label(newWindow, image=img)

    lbl.pack()

    newWindow.mainloop()


def ask():
    if tkinter.messagebox.askokcancel('', '프로그램을 종료하시겠습니까?'):  # 종료할지 묻는 팝업창 -> 확인 누를 경우
        window.destroy()  # 프레임 파괴
        window.quit()  # 프레임 종료
        exit()  # 프로그램 종료


img1 = PhotoImage(file='android01.gif')  # 이미지 불러옴
img2 = PhotoImage(file='android02.gif')
img3 = PhotoImage(file='android03.gif')
img4 = PhotoImage(file='android04.gif')
img5 = PhotoImage(file='android05.gif')
img6 = PhotoImage(file='android06.gif')

btn1 = Button(window, image=img1, width=180, height=180)  # 이미지 버튼 생성
btn2 = Button(window, image=img2, width=180, height=180, command=action1)
btn3 = Button(window, image=img3, width=180, height=180)
btn4 = Button(window, image=img4, width=180, height=180)
btn5 = Button(window, image=img5, width=180, height=180, command=action2)
btn6 = Button(window, image=img6, width=180, height=180)

btn1.place(x=0, y=0)  # 배치
btn2.place(x=180, y=0)
btn3.place(x=360, y=0)
btn4.place(x=0, y=180)
btn5.place(x=180, y=180)
btn6.place(x=360, y=180)

window.mainloop()  # 실행
