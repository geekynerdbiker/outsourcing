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
data_fig = None


def job():
    global tick_index

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


def init():
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

    plt.figure(figsize=(12, 8))
    plt.plot(daily_vals)
    plt.xticks(np.arange(0, 2, 0.2), labels=['Jan', '', 'Feb', '', 'Mar', '', 'May', '', 'June', '', 'July'])
    plt.xlabel('Time')
    plt.ylabel('Usage(kWh)')
    plt.savefig('static/data.jpg')

    tick_index = len(daily_vals)


app = Flask(__name__)
schedule = BackgroundScheduler(daemon=True, timezone='Asia/Seoul')
schedule.add_job(job, 'interval', seconds=900)
schedule.start()


@app.route('/css/<path:filename>')
def serve_css(filename):
    return send_from_directory('css', filename)


@app.route('/', methods=['POST', 'GET'])
def index():
    return render_template('index.html', fig='data.jpg', tick=ticks, data=daily_vals)


if __name__ == '__main__':
    init()
    app.run(host='127.0.0.1', port=5001)
