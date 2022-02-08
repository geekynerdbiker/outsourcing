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

    def delete(self, table):
        sql = "DROP TABLE {table} ;".format(table=table)

        try:
            self.cursor.execute(sql)
            self.db.commit()
        except Exception as e:
            print(" create DB  ", e)

    def insert(self, table, data, primary_key):
        sql = "INSERT INTO {table} VALUES ({data}) ON CONFLICT ({primary_key}) DO NOTHING;".format(table=table, data=data, primary_key=primary_key)

        try:
            self.cursor.execute(sql)
            self.db.commit()
        except Exception as e:
            print(" insert DB  ", e)
            print(data)


# file_path='C://task_metadata.json'
file_path = 'task_metadata.json'
# file_path = 'manager_config.json'
with open(file_path, 'r', encoding='utf-8') as f:
    json_data = json.load(f)

db = Databases()
for dname in json_data.keys():
    print(f'[------ list name = {dname} ------]')
    i = 0
    l = list(json_data[dname][0].keys())
    keys = []
    primary_key = ''

    for k in range(len(l)):
        if k == 0:
            primary_key = l[k]
            l[k] += ' varchar(255) primary key'
        else:
            l[k] += ' varchar(255)'
        keys.append(l[k])

    keys = str(keys)
    keys = keys.replace('[', '').replace('\'', '').replace(']', '')

    db.delete(dname.lower())
    db.create(dname, keys)

    for datas in json_data[dname]:
        # print(f'[--------- item {i + 1} ---------]')
        i += 1
        s = str(datas.values())
        s = s[12:len(s) - 1]
        # print(s)

        data = []
        for key, value in datas.items():
            data.append(value.replace(' ', '_').replace('\'', ''))

        data = str(data)
        data = data.replace('[', '').replace(']', '')

        db.insert(table=dname, data=data, primary_key=primary_key)
