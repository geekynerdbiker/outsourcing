from ctypes import *
import keyboard
from PIL import Image, ImageGrab
import pygetwindow as gw
import time
import tkinter

dd_dll = windll.LoadLibrary('./dd40605x64.dll')
win = gw.getWindowsWithTitle('Gersang')[0]


def init():
    try:
        win.activate()
        print('[ Initialized ] Gersang is running.')
    except IndexError:
        print('[ Error ] Gersang not started.')
        exit(101)

    if dd_dll.DD_btn(0) == 1:
        print("[ Initialized ] Library loaded.")
        return True
    else:
        print("[ Initialized ] Could not load library.")
        exit(101)


def stop():
    dd_dll.DD_key(210, 1)
    time.sleep(0.01)
    dd_dll.DD_key(210, 2)

    dd_dll.DD_key(402, 1)
    time.sleep(0.01)
    dd_dll.DD_key(402, 2)


def debuf():
    dd_dll.DD_key(301, 1)
    time.sleep(0.01)
    dd_dll.DD_key(301, 2)

    dd_dll.DD_key(302, 1)
    time.sleep(0.01)
    dd_dll.DD_key(302, 2)

    dd_dll.DD_key(102, 1)
    time.sleep(0.01)
    dd_dll.DD_key(102, 2)


def attack():
    dd_dll.DD_key(204, 1)
    time.sleep(0.01)
    dd_dll.DD_key(204, 2)

    dd_dll.DD_key(303, 1)
    time.sleep(0.01)
    dd_dll.DD_key(303, 2)

    dd_dll.DD_key(203, 1)
    time.sleep(0.01)
    dd_dll.DD_key(203, 2)

    dd_dll.DD_key(303, 1)
    time.sleep(0.01)
    dd_dll.DD_key(303, 2)

    dd_dll.DD_key(202, 1)
    time.sleep(0.01)
    dd_dll.DD_key(202, 2)

    dd_dll.DD_key(303, 1)
    time.sleep(0.01)
    dd_dll.DD_key(303, 2)

    dd_dll.DD_key(201, 1)
    time.sleep(0.01)
    dd_dll.DD_key(201, 2)

    dd_dll.DD_key(303, 1)
    time.sleep(0.01)
    dd_dll.DD_key(303, 2)

    dd_dll.DD_key(200, 1)
    time.sleep(0.01)
    dd_dll.DD_key(200, 2)

    dd_dll.DD_key(303, 1)
    time.sleep(0.01)
    dd_dll.DD_key(303, 2)

    return


def capture():
    image = ImageGrab.grab(bbox=(win.left, win.top, win.right, win.bottom)).convert('L')
    image.save('captue.png')
    data = image.load()


def run():
    print("[ Notice ] Hot keys are activated.")
    while True:
        if keyboard.is_pressed('f12'):
            print("[ Notice ] Hot keys are inactivated.")
            break

        time.sleep(0.01)
        if keyboard.is_pressed('z'):
            debuf()
        if keyboard.is_pressed('x'):
            for i in range(2):
                attack()
        if keyboard.is_pressed('c'):
            stop()
        # if keyboard.is_pressed('v'):
        #     capture()


init()

root = tkinter.Tk()

width = root.winfo_screenwidth()
height = root.winfo_screenheight()

root.geometry("200x100+" + str(100) + '+' + str(100))

btn = tkinter.Button(root, text='Run', command=run)
btn.pack()

root.mainloop()
