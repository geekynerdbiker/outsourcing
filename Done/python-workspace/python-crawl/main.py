from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from datetime import datetime, timedelta
from selenium.webdriver.common.by import By
import csv

f = open('lunch.csv', 'w', newline='', encoding='UTF-8')
sheet = csv.writer(f)
sheet.writerow(["NAME", "SCHOOL", "PRICE", "DATE", "VOTE"])

# today = datetime.today().strftime("%Y-%m-%d")
today = datetime.today()
start = today - timedelta(today.weekday())

chrome_options = Options()
chrome_options.add_argument("--headless")

driver = webdriver.Chrome(options=chrome_options)
driver.implicitly_wait(5)

while True:
    url = 'https://snuco.snu.ac.kr/foodmenu/?date=' + start.strftime("%Y-%m-%d") + '&orderby=DESC'

    driver.get(url)

    table = driver.find_element(By.XPATH, '//*[@id="celeb-mealtable"]/table')
    tbody = table.find_element(By.TAG_NAME, "tbody")

    i = 1

    rows = tbody.find_elements(By.TAG_NAME, "tr")
    for index, value in enumerate(rows):
        name = value.find_elements(By.TAG_NAME, "td")[0].text
        lunch = value.find_elements(By.TAG_NAME, "td")[2].text

        if '학생회관식당' in name:
            if '휴점' in lunch:
                break

            menus = lunch.split('\n')
            for m in menus:
                if m != '':
                    date = str(start.year)+'-'+str(start.month)+'-'+str(start.day)
                    sheet.writerow([m.split('  ')[0], '서울대학교', m.split('  ')[1].replace('원',''), date, '0'])
                else:
                    break
            break

    if start.weekday() == 6:
        break
    start += timedelta(1)

f.close()
driver.close()