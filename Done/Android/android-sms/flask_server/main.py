from flask import Flask, request
import sqlite3, re
import requests

from selenium import webdriver
import time

from bs4 import BeautifulSoup
from selenium.webdriver import Keys
from selenium.webdriver.common.by import By

app = Flask(__name__)


@app.route('/result', methods=['POST'])
def func():
    data = request.get_json()
    contents = data['contents']
    url = find_url(contents)
    result = True

    if len(url) != 0:
        result = is_sms_phishing(url[0])

    db_init()
    db_insert(data, url)
    db_print()

    print(str(result))
    return str(result)


def find_url(s):
    regex = r"(?i)\b((?:https?://|www\d{0,3}[.]|[a-z0-9.\-]+[.][a-z]{2,4}/)(?:[^\s()<>]+|\(([^\s()<>]+|(\([^\s()<>]+\)))*\))+(?:\(([^\s()<>]+|(\([^\s()<>]+\)))*\)|[^\s`!()\[\]{};:'\".,<>?«»“”‘’]))"
    url = re.findall(regex, s)
    return [x[0] for x in url]


def is_sms_phishing(url):
    """
    Web Driver 경로 수정!

    :param url:
    :return:
    """
    driver = webdriver.Chrome("/usr/local/bin/chromedriver")

    driver.get('https://www.rancert.com/check_url.php')
    time.sleep(1)

    button = driver.find_element(By.XPATH, '//*[@id="contents"]/div/div[2]/form/dl/dd/span/input')
    element = driver.find_element(By.NAME, 'strUrl')
    element.send_keys(url)
    button.click()

    table = driver.find_element(By.XPATH, '//*[@id="contents"]/div/div[2]/table')
    tbody = table.find_element(By.TAG_NAME, "tbody")
    rows = tbody.find_elements(By.TAG_NAME, "tr")

    for index, value in enumerate(rows):
        body = value.find_elements(By.TAG_NAME, "td")[1]

        if body.text != "clean site" and body.text != "unrated site":
            return False
    return True


def db_init():
    conn = sqlite3.connect("sms.db")
    conn.execute(
        'CREATE TABLE IF NOT EXISTS sms(id INTEGER primary key autoincrement, sender TEXT, date TEXT, url TEXT, contents TEXT)')
    conn.commit()


def db_insert(data, url):
    conn = sqlite3.connect("sms.db")
    cur = conn.cursor()

    if len(url) == 0:
        url.append("")

    cur.execute('INSERT INTO sms (sender, date, url, contents) values (?,?,?,?)',
                (data['sender'], data['receivedDate'], url[0], data['contents']))
    conn.commit()


def db_print():
    con = sqlite3.connect('sms.db')
    cursor = con.cursor()
    cursor.execute("SELECT * FROM sms ;")
    print(cursor.fetchall())


if __name__ == '__main__':
    # is_sms_phishing(find_url("www.naver.com"))
    app.run(host='127.0.0.1', port=8080)
