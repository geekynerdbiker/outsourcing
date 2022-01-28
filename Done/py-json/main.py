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

    def insert(self, schema, table, column, data):
        sql = " INSERT INTO {schema}.{table}({column}) VALUES ('{data}') ;".format(schema=schema, table=table,
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

# db = Databases()
# db.insert(schema='test', table='table', column=0, data='data')


for keys in json_data.keys():
    print(f'[------ list name = {keys} ------]')
    i = 0
    for data in json_data[keys]:
        print(f'[--------- item {i+1} ---------]')
        i += 1
        for key, value in data.items():
            print(f'{key} : {value}')
