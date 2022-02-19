import os
from flask import Flask, render_template
from models import db

app = Flask('SMS')


@app.route('/')
def hello():
    return render_template('hello.html')


directory = os.path.abspath(os.path.dirname(__file__))
db_file = os.path.join(directory, 'sms.db')

app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///' + db_file
app.config['SQLALCHEMY_COMMIT_ON_TEARDOWN'] = True
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

db.init_app(app)
db.app = app
db.create_all()

app.run(host='127.0.0.1', port=8080, debug=True)
