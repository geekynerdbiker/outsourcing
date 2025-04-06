from ctypes import *
import keyboard
from PIL import ImageGrab
import pygetwindow as gw
import time
import tkinter
from threading import Thread, Event


class App:
    def __init__(self, root):
        self.dd_dll = windll.LoadLibrary('./dd40605x64.dll')
        # self.win = gw.getWindowsWithTitle('Gersang')[0]

        # try:
        #     self.win.activate()
        #     print('[ Initialized ] Gersang is running.')
        # except IndexError:
        #     print('[ Error ] Gersang not started.')
        #     exit(101)

        if self.dd_dll.DD_btn(0) == 1:
            # print("[ Initialized ] Library loaded.")
            pass
        else:
            print("[ Initialized ] Could not load library.")
            exit(101)

        self.thread = None
        self.stop_event = Event()
        self.root = root

        self.root.geometry("250x150+100+100")

        # Debuf Frame
        self.frame_debuf_delay = tkinter.Frame(self.root)

        self.label_debuf_delay = tkinter.Label(self.frame_debuf_delay, width=15, text='Debuf Delay', justify='left')
        self.label_debuf_delay.grid(row=1, column=1)

        self.ent_debuf_delay = tkinter.Entry(self.frame_debuf_delay, width=5, justify='right')
        self.ent_debuf_delay.insert(0, '45')
        self.ent_debuf_delay.grid(row=1, column=2)

        self.label_debuf_delay2 = tkinter.Label(self.frame_debuf_delay, width=2, text='ms')
        self.label_debuf_delay2.grid(row=1, column=3)

        self.frame_debuf_delay.pack()

        # Attack Frame
        self.frame_atk_delay = tkinter.Frame(self.root)

        self.label_atk_delay = tkinter.Label(self.frame_atk_delay, width=15, text='Attack Delay', justify='left')
        self.label_atk_delay.grid(row=1, column=1)

        self.ent_atk_delay = tkinter.Entry(self.frame_atk_delay, width=5, justify='right')
        self.ent_atk_delay.insert(0, '45')
        self.ent_atk_delay.grid(row=1, column=2)

        self.label_atk_delay2 = tkinter.Label(self.frame_atk_delay, width=2, text='ms')
        self.label_atk_delay2.grid(row=1, column=3)

        self.frame_atk_delay.pack()

        # Main Dealer Frame
        self.frame_main = tkinter.Frame(self.root)

        self.label_main = tkinter.Label(self.frame_main, width=15, text='Main Dealer', justify='left')
        self.label_main.grid(row=1, column=1)

        self.ent_main = tkinter.Entry(self.frame_main, width=5, justify='right')
        self.ent_main.insert(0, '5')
        self.ent_main.grid(row=1, column=2)

        self.label_main2 = tkinter.Label(self.frame_main, width=5, text='times')
        self.label_main2.grid(row=1, column=3)

        self.frame_main.pack()


        # Sub Dealer Frame
        self.frame_sub = tkinter.Frame(self.root)

        self.label_sub = tkinter.Label(self.frame_sub, width=15, text='Sub Dealer', justify='left')
        self.label_sub.grid(row=1, column=1)

        self.ent_sub = tkinter.Entry(self.frame_sub, width=5, justify='right')
        self.ent_sub.insert(0, '3')
        self.ent_sub.grid(row=1, column=2)

        self.label_sub2 = tkinter.Label(self.frame_sub, width=5, text='times')
        self.label_sub2.grid(row=1, column=3)

        self.frame_sub.pack(side='top')

        # Label Frame
        self.frame_label = tkinter.Frame(self.root)

        self.label_status = tkinter.Label(self.frame_label, text='PRESS F9 TO START...')
        self.label_status.pack()

        # self.label_notification = tkinter.Label(self.frame_label, text='PRESS F9 TO START...')
        # self.label_notification.pack(side='bottom')

        self.frame_label.pack(side='bottom')

        # Add Hotkeys
        keyboard.add_hotkey('f9', self.start_thread)
        keyboard.add_hotkey('f10', self.stop_thread)
        keyboard.add_hotkey('shift+z', self.debuf_threaded)
        keyboard.add_hotkey('shift+x', self.attack_threaded)

        self.active = False

    def debuf_threaded(self):
        if not self.active:
            return
        for key in [101, 301, 302]:
            self.dd_dll.DD_key(key, 1)
            time.sleep(int(self.ent_atk_delay.get()) / 1000)
            self.dd_dll.DD_key(key, 2)
            time.sleep(int(self.ent_atk_delay.get()) / 1000)

    def attack_threaded(self):
        if not self.active:
            return
        if self.thread is None or not self.thread.is_alive():
            try:
                k1 = int(self.ent_main.get())
                k2 = int(self.ent_sub.get())
                self.thread = Thread(target=self.attack, args=(k1, k2), daemon=True)
                self.thread.start()
            except ValueError:
                print("[Error] 공격 횟수 입력이 잘못됨.")

    def attack(self, k1, k2):
        sequence = [
            204, 304,
            203,
            *[303 for _ in range(k2)],
            202,
            *[303 for _ in range(k2)],
            201,
            *[303 for _ in range(k2)],
            200,
            *[303 for _ in range(k1)],
            204,
            *[402 for _ in range(k2)],
            200
        ]16
        for key in sequence:
            self.dd_dll.DD_key(key, 1)
            time.sleep(int(self.ent_atk_delay.get()) / 1000)
            self.dd_dll.DD_key(key, 2)
            time.sleep(int(self.ent_atk_delay.get()) / 1000)

    # def capture(self):
    #     image = ImageGrab.grab(bbox=(self.win.left, self.win.top, self.win.right, self.win.bottom)).convert('L')
    #     image.save('capture.png')

    def start_thread(self):
        self.active = True
        self.label_status.config(text='Hotkey Activated!')
        # print("[Info] 스크립트 활성화됨")

    def stop_thread(self):
        self.active = False
        self.label_status.config(text='Inactivated.')
        self.stop_event.set()
        if self.thread and self.thread.is_alive():
            self.thread.join(timeout=1)
        # print("[Info] 스크립트 중단됨")


root = tkinter.Tk()
app = App(root)
root.mainloop()
