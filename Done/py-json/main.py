import json
import psycopg2


class Databases:
    def __init__(self):
        self.db = psycopg2.connect(host='localhost', dbname='test', user='postgres', password='0000', port=5432)
        self.cursor = self.db.cursor()

    def __del__(self):
        self.db.close()
        self.cursor.close()

    def execute(self, query, args={}):
        self.cursor.execute(query, args)
        row = self.cursor.fetchall()
        return row

    def commit(self):
        self.cursor.commit()

    def create(self, table, structure):
        sql = "CREATE TABLE {table} ({structure}) ;".format(table=table, structure=structure)

        try:
            self.cursor.execute(sql)
            self.db.commit()
        except Exception as e:
            print(" create DB  ", e)

    def insert(self, table, column, data):
        sql = "INSERT INTO {table}({column}) VALUES ({data}) ;".format(table=table,
                                                                          column=column, data=data)
        try:
            self.cursor.execute(sql)
            self.db.commit()
        except Exception as e:
            print(" insert DB  ", e)


# file_path='C://task_metadata.json'
file_path = 'task_metadata.json'
with open(file_path, 'r', encoding='utf-8') as f:
    json_data = json.load(f)

db = Databases()
for keys in json_data.keys():
    print(f'[------ list name = {keys} ------]')
    i = 0
    for datas in json_data[keys]:
        print(f'[--------- item {i + 1} ---------]')
        i += 1
        s = str(datas.values())
        s = s[12:len(s) - 1]
        print(s)

        column, data = [], []
        for key, value in datas.items():
            column.append(key)
            data.append(value)

        column = str(column)
        column = column.replace('[', '').replace('\'', '').replace(']', '')

        data = str(data)
        data = data.replace('[', '').replace(']', '')

        db.insert(table=keys, column=column, data=data)
