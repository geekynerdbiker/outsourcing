import sqlite3
import models

connection = None


class Model:
    def __init__(self, **kwargs):
        self.data = {}
        for key, value in kwargs.items():
            self.data[key] = value

    @classmethod
    def create_table(cls, dbname):
        global connection
        connection = sqlite3.connect(dbname + '.sqlite3')
        table_name = cls.__name__.lower()
        fields = [
            'id INTEGER PRIMARY KEY AUTOINCREMENT'
        ]
        arguments = vars(cls)
        for key in vars(cls).keys():
            if models.instanceof(arguments[key]):
                field_type = arguments[key]
                data_type = field_type.type
                column = f"{key} {data_type}"
                if (isinstance(field_type, models.EmailField)):
                    column = f"{key} TEXT NOT NULL"
                    if field_type.unique:
                        column = f"{key} TEXT NOT NULL UNIQUE"
                if isinstance(field_type, models.BooleanField):
                    column = f"{key} INTEGER DEFAULT {int(field_type.default)}"
                fields.append(column)

        fields = ', '.join(fields)
        sql = f"CREATE TABLE IF NOT EXISTS {table_name} ({fields})"
        cursor = connection.cursor()
        cursor.execute(sql)
        connection.commit()
        return True

    @classmethod
    def get_table_name(cls):
        return cls.__name__.lower()

    def save(self):
        global connection
        tablename = self.get_table_name()
        fields = ', '.join(self.data.keys())
        field_references = ', '.join('?' for i in range(len(self.data)))
        sql = 'INSERT INTO %s (%s) VALUES (%s)'
        sql = sql % (tablename, fields, field_references)
        cursor = connection.cursor()
        cursor.execute(sql, tuple(self.data.values()))
        connection.commit()
        return True

    @classmethod
    def get(cls, id=None):
        if not id:
            raise ValueError("id is required")
        global connection
        tablename = cls.__name__.lower()
        sql = f"SELECT * FROM {tablename} WHERE id=:id"
        cursor = connection.cursor()
        record = cursor.execute(sql, {"id": id}).fetchone()
        if not record:
            raise ValueError(f"An item with with id '{id}' was not found")
        else:
            return cls.format(record[1:])

    @classmethod
    def format(cls, values):
        fields = vars(cls)
        keys = []
        for key, value in cls.__dict__.items():
            if models.instanceof(fields[key]):
                keys.append(key)
        return dict(zip(keys, values))

    @classmethod
    def filter(cls, **kwargs):
        global connection
        tablename = cls.__name__.lower()
        query_params = '=?'.join(kwargs.keys()) + "=?"
        sql = "SELECT * FROM %s where %s"
        sql = sql % (tablename, query_params)
        cursor = connection.cursor()
        results = cursor.execute(sql, tuple(kwargs.values())).fetchall()
        formated_results = [cls.format(row[1:]) for row in results]
        return formated_results


def create_db(name):
    global connection
    connection = sqlite3.connect(f'{name}.sqlite3')
    return name