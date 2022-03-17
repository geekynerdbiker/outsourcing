from flask_sqlalchemy import SQLAlchemy

db = SQLAlchemy()


class SMS(db.Model):
    __tablename__ = "SMS"
    id = db.Column(db.Integer, primary_key=True)
    sender = db.Column(db.String(16))
    receivecDate = db.Column(db.String(32))
    url = db.Column(db.String(256))
    contents = db.Column(db.String(512))
