from flask import Flask, render_template, send_from_directory, request, redirect, url_for
from apscheduler.schedulers.background import BackgroundScheduler
from datetime import datetime
import requests
import json
import matplotlib
import matplotlib.pyplot as plt

matplotlib.use('agg')

customer = '0144436055'
service_key = 'oz11k4f290y8q182d419'

ticks = []
periods = []
daily_vals = []
period_vals = []
today = datetime.today().strftime("%Y%m%d")

tick_index = 0
str_data = []
str_counter = 0
str_line = 0
data_fig = None


def job():
    global today
    global daily_vals
    global str_data
    global str_counter
    global str_line
    global tick_index

    if today != datetime.today().strftime("%Y%m%d"):
        today = datetime.today().strftime("%Y%m%d")
        daily_vals = []

    url = 'https://opm.kepco.co.kr:11080/OpenAPI/getMinuteLpData.do?custNo=' + customer + '&dateTime=' + today + ticks[
        tick_index] + '&serviceKey=' + service_key + '&returnType=02'
    data = json.loads(requests.get(url).text)['minuteLpDataInfoList'][0]
    if 'pwr_qty' not in data:
        print('No new data.')
        return

    daily_vals.append(data['pwr_qty'])
    tick_index += 1
    if tick_index == len(ticks):
        tick_index = 0
    plt.figure(figsize=(50, 8))
    plt.plot(ticks[:len(daily_vals)], daily_vals)
    plt.xlabel('Time')
    plt.ylabel('Usage(kWh)')
    plt.savefig('static/data.jpg')

    if str_counter < 4:
        if str_counter == 0:
            l = [f'Time: {ticks[len(daily_vals)-1]} / Usage: {data["pwr_qty"]} kWh']
            str_data.append(l)
        else:
            str_data[str_line].append(f'Time: {ticks[len(daily_vals)-1]} / Usage: {data["pwr_qty"]} kWh')
        str_counter += 1

    if str_counter == 4:
        str_counter = 0
        str_line += 1

    if str_line == 25:
        str_data = []
        str_counter = 0
        str_line = 0


def init():
    global str_data
    global str_counter
    global str_line
    global tick_index
    global daily_vals

    for i in range(25):
        for j in range(4):
            if i == 0 and j == 0:
                continue
            if i == 24 and j != 0:
                continue
            ticks.append(str(i).zfill(2) + str(j * 15).zfill(2))

    url = 'https://opm.kepco.co.kr:11080/OpenAPI/getDayLpData.do?custNo=' + customer + '&date=' + today + '&serviceKey=' + service_key + '&returnType=02'
    daily = json.loads(requests.get(url).text)['dayLpDataInfoList'][0]

    key = 'pwr_qty'

    for t in ticks:
        temp_key = key + t
        if daily[temp_key] == '':
            break
        daily_vals.append(daily[temp_key])

    for i in range(len(daily_vals)):
        if str_counter < 4:
            if str_counter == 0:
                l = [f'Time: {ticks[i]} / Usage: {daily_vals[i]} kWh']
                str_data.append(l)
            else:
                str_data[str_line].append(f'Time: {ticks[i]} / Usage: {daily_vals[i]} kWh')
            str_counter += 1

        if str_counter == 4:
            str_counter = 0
            str_line += 1

        if str_line == 25:
            str_data = []
            str_counter = 0
            str_line = 0

    plt.figure(figsize=(50, 8))
    plt.plot(ticks[:len(daily_vals)], daily_vals)
    plt.xlabel('Time')
    plt.ylabel('Usage(kWh)')
    plt.savefig('static/data.jpg')

    tick_index = len(daily_vals)
    print(str_data)


app = Flask(__name__)
schedule = BackgroundScheduler(daemon=True, timezone='Asia/Seoul')
schedule.add_job(job, 'interval', seconds=900)
schedule.start()


@app.route('/css/<path:filename>')
def serve_css(filename):
    return send_from_directory('css', filename)


@app.route('/', methods=['POST', 'GET'])
def index():
    return render_template('index.html', fig='data.jpg', data=str_data)


if __name__ == '__main__':
    init()
    app.run(host='127.0.0.1', port=5001)
