from flask import Flask, make_response, jsonify, request
import sqlite3

app = Flask(__name__)


@app.route('/database', methods=['POST'])
def hello():
    data = request.get_json()
    db_init()
    db_insert(data)
    contents = data['contents']
    db_print()
    return jsonify({'data': data})


def find_url(str):
    regex = r"(?i)\b((?:https?://|www\d{0,3}[.]|[a-z0-9.\-]+[.][a-z]{2,4}/)(?:[^\s()<>]+|\(([^\s()<>]+|(\([^\s()<>]+\)))*\))+(?:\(([^\s()<>]+|(\([^\s()<>]+\)))*\)|[^\s`!()\[\]{};:'\".,<>?«»“”‘’]))"
    url = re.findall(regex, str)
    return [x[0] for x in url]


def is_sms_phishing(contents):
    urls = find_url(contents)


def db_init():
    conn = sqlite3.connect("sms.db")
    conn.execute(
        'CREATE TABLE IF NOT EXISTS sms(id INTEGER primary key autoincrement, sender TEXT, date TEXT, contents TEXT)')
    conn.commit()


def db_insert(data):
    conn = sqlite3.connect("sms.db")
    cur = conn.cursor()
    cur.execute('INSERT INTO sms (sender, date, contents) values (?,?,?)',
                (data['sender'], data['receivedDate'], data['contents']))
    conn.commit()


def db_print():
    con = sqlite3.connect('sms.db')
    cursor = con.cursor()
    cursor.execute("SELECT * FROM sms ;")
    print(cursor.fetchall())


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=8080)
