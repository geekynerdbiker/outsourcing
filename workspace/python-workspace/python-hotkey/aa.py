from ctypes import *
import keyboard
from PIL import Image, ImageGrab
import pygetwindow as gw
import time
import tkinter
from threading import Thread, Event


class App:
    def __init__(self, root):
        self.dd_dll = windll.LoadLibrary('./dd40605x64.dll')
        self.win = gw.getWindowsWithTitle('Gersang')[0]

        try:
            self.win.activate()
            print('[ Initialized ] Gersang is running.')
        except IndexError:
            print('[ Error ] Gersang not started.')
            exit(101)

        if self.dd_dll.DD_btn(0) == 1:
            print("[ Initialized ] Library loaded.")
        else:
            print("[ Initialized ] Could not load library.")
            exit(101)

        self.thread = None
        self.stop_event = Event()

        self.root = root

        self.width = self.root.winfo_screenwidth()
        self.height = self.root.winfo_screenheight()

        self.root.geometry("200x100+" + str(100) + '+' + str(100))

        self.btn = tkinter.Button(self.root, text='Start', command=self.start_thread)
        self.btn.pack()

        self.ent = tkinter.Entry(self.root)
        self.ent.insert(0, '3')
        self.ent.pack()

        self.ent2 = tkinter.Entry(self.root)
        self.ent2.insert(0, '4')
        self.ent2.pack()

        self.label = tkinter.Label(self.root)
        self.label.pack()

    def stop(self):
        self.dd_dll.DD_key(204, 1)
        time.sleep(0.015)
        self.dd_dll.DD_key(204, 2)
        time.sleep(0.015)

        self.dd_dll.DD_key(402, 1)
        time.sleep(0.015)
        self.dd_dll.DD_key(402, 2)
        time.sleep(0.015)

        self.dd_dll.DD_key(201, 1)
        time.sleep(0.015)
        self.dd_dll.DD_key(201, 2)
        time.sleep(0.015)

    def debuf(self):
        self.dd_dll.DD_key(101, 1)
        time.sleep(0.015)
        self.dd_dll.DD_key(101, 2)
        time.sleep(0.015)

        self.dd_dll.DD_key(301, 1)
        time.sleep(0.015)
        self.dd_dll.DD_key(301, 2)
        time.sleep(0.015)

        self.dd_dll.DD_key(302, 1)
        time.sleep(0.015)
        self.dd_dll.DD_key(302, 2)
        time.sleep(0.015)

    def attack(self, k1, k2):
        self.dd_dll.DD_key(204, 1)
        time.sleep(0.015)
        self.dd_dll.DD_key(204, 2)
        time.sleep(0.015)

        self.dd_dll.DD_key(304, 1)
        time.sleep(0.015)
        self.dd_dll.DD_key(304, 2)
        time.sleep(0.015)

        self.dd_dll.DD_key(203, 1)
        time.sleep(0.015)
        self.dd_dll.DD_key(203, 2)
        time.sleep(0.015)

        for i in range(k1):
            self.dd_dll.DD_key(303, 1)
            time.sleep(0.015)
            self.dd_dll.DD_key(303, 2)
            time.sleep(0.015)

        self.dd_dll.DD_key(202, 1)
        time.sleep(0.015)
        self.dd_dll.DD_key(202, 2)
        time.sleep(0.015)

        for i in range(k1):
            self.dd_dll.DD_key(303, 1)
            time.sleep(0.015)
            self.dd_dll.DD_key(303, 2)
            time.sleep(0.015)

        self.dd_dll.DD_key(201, 1)
        time.sleep(0.015)
        self.dd_dll.DD_key(201, 2)
        time.sleep(0.015)

        for i in range(k1):
            self.dd_dll.DD_key(303, 1)
            time.sleep(0.015)
            self.dd_dll.DD_key(303, 2)
            time.sleep(0.015)

        self.dd_dll.DD_key(200, 1)
        time.sleep(0.015)
        self.dd_dll.DD_key(200, 2)
        time.sleep(0.015)

        for i in range(k2):
            self.dd_dll.DD_key(303, 1)
            time.sleep(0.015)
            self.dd_dll.DD_key(303, 2)
            time.sleep(0.015)

    def capture(self):
        image = ImageGrab.grab(bbox=(self.win.left, self.win.top, self.win.right, self.win.bottom)).convert('L')
        image.save('captue.png')

    def run(self):
        # print("[ Notice ] Hot keys are activated.")
        self.label.config(text='activated!')
        while True:
            if keyboard.is_pressed('f10'):
                self.stop_thread()
                self.label.config(text='inactivated')
                return
            if keyboard.is_pressed('z'):
                self.debuf()
            if keyboard.is_pressed('x'):
                self.attack(int(self.ent.get()), int(self.ent2.get()))
            if keyboard.is_pressed('c'):
                self.stop()

    def start_thread(self):
        if self.thread is None or not self.thread.is_alive():
            self.stop_event.clear()
            self.thread = Thread(target=self.run)
            self.thread.start()

    def stop_thread(self):
        if self.thread is not None:
            self.stop_event.set()


root = tkinter.Tk()
app = App(root)
root.mainloop()
