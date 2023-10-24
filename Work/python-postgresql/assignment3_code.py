import psycopg
from psycopg import sql
import os
from typing import Union


# problem 1
def entire_search(CONNECTION: str, table_name: str) -> list:
    with psycopg.connect(CONNECTION) as conn:
        cur = conn.cursor()
        cur.execute(f"SELECT * FROM myschema.{table_name}")
        conn.commit()
    return cur.fetchall()


# problem 2
def registration_history(CONNECTION: str, student_id: str) -> Union[list, None]:
    result = []
    with psycopg.connect(CONNECTION) as conn:
        cur = conn.cursor()
        cur.execute(f'SELECT * FROM myschema.students WHERE "STUDENT_ID" = \'{student_id}\'')
        conn.commit()

        if len(cur.fetchall()) == 0:
            print('Not Exist student with STUDENT ID:', student_id)
            return None

        cur.execute(f'SELECT "COURSE_ID" FROM myschema.course_registration WHERE "STUDENT_ID" = \'{student_id}\'')
        conn.commit()

        for id in cur.fetchall():
            cur.execute(
                f'SELECT "YEAR", "SEMESTER", "COURSE_ID_PREFIX", "COURSE_ID_NO", "DIVISION_NO", "COURSE_NAME", '
                f'"PROF_ID", "CREDIT" FROM myschema.course WHERE "COURSE_ID" = \'{id[0]}\'')
            conn.commit()
            result.append(cur.fetchall()[0])
        return sorted(result, key=lambda x: (x[0], x[1], x[5]))


# problem 3
def registration(CONNECTION: str, course_id: int, student_id: str) -> Union[list, None]:
    with psycopg.connect(CONNECTION) as conn:
        cur = conn.cursor()
        cur.execute(f'SELECT * FROM myschema.course WHERE "COURSE_ID" = {course_id}')
        conn.commit()

        if len(cur.fetchall()) == 0:
            print('Not Exist course with COURSE ID:', course_id)
            return None

        cur.execute(f'SELECT * FROM myschema.students WHERE "STUDENT_ID" = \'{student_id}\'')
        conn.commit()

        if len(cur.fetchall()) == 0:
            print('Not Exist student with STUDENT ID:', student_id)
            return None

        cur.execute(f'SELECT * FROM myschema.course_registration WHERE "STUDENT_ID" = \'{student_id}\' AND "COURSE_ID" = {course_id}')
        conn.commit()

        if len(cur.fetchall()) != 0:
            cur.execute(f'SELECT "COURSE_NAME" FROM myschema.course WHERE "COURSE_ID" = {course_id}')
            conn.commit()

            print(student_id, 'is already registered in', cur.fetchall()[0][0])
            return None

        cur.execute(f'INSERT INTO myschema.course_registration("COURSE_ID", "STUDENT_ID") VALUES({course_id},\'{student_id}\')')
        conn.commit()

        cur.execute(f'SELECT * FROM myschema.course_registration')
        conn.commit()

        return cur.fetchall()



# problem 4
def withdrawal_registration(CONNECTION: str, course_id: int, student_id: str) -> Union[list, None]:
    with psycopg.connect(CONNECTION) as conn:
        cur = conn.cursor()
        cur.execute(f'SELECT * FROM myschema.course WHERE "COURSE_ID" = {course_id}')
        conn.commit()

        if len(cur.fetchall()) == 0:
            print('Not Exist course with COURSE ID:', course_id)
            return None

        cur.execute(f'SELECT * FROM myschema.students WHERE "STUDENT_ID" = \'{student_id}\'')
        conn.commit()

        if len(cur.fetchall()) == 0:
            print('Not Exist student with STUDENT ID:', student_id)
            return None

        cur.execute(
            f'SELECT * FROM myschema.course_registration WHERE "STUDENT_ID" = \'{student_id}\' AND "COURSE_ID" = {course_id}')
        conn.commit()

        if len(cur.fetchall()) == 0:
            cur.execute(f'SELECT "COURSE_NAME" FROM myschema.course WHERE "COURSE_ID" = {course_id}')
            conn.commit()

            print(student_id, 'is not registered in', cur.fetchall()[0][0])
            return None

        cur.execute(
            f'DELETE FROM myschema.course_registration WHERE "COURSE_ID" = {course_id} AND "STUDENT_ID" = \'{student_id}\'')
        conn.commit()

        cur.execute(f'SELECT * FROM myschema.course_registration')
        conn.commit()

        return cur.fetchall()


# problem 5
def modify_lectureroom(CONNECTION: str, course_id: int, buildno: str, roomno: str) -> Union[list, None]:
    with psycopg.connect(CONNECTION) as conn:
        cur = conn.cursor()
        cur.execute(f'SELECT * FROM myschema.lectureroom WHERE "BUILDNO" = \'{buildno}\' AND "ROOMNO" = \'{roomno}\'')
        conn.commit()

        if len(cur.fetchall()) == 0:
            print('Not Exist lecture room with BUILD NO:', buildno, '/ ROOM NO:', roomno)
            return None

        cur.execute(f'SELECT * FROM myschema.course WHERE "COURSE_ID" = {course_id}')
        conn.commit()

        if len(cur.fetchall()) == 0:
            print('Not Exist course with COURSE ID:', course_id)
            return None

        cur.execute(
            f'UPDATE myschema.course SET "BUILDNO" = \'{buildno}\', "ROOMNO" = \'{roomno}\' WHERE "COURSE_ID" = {course_id}')
        conn.commit()

        cur.execute(f'SELECT * from myschema.course')
        conn.commit()
        return cur.fetchall()


# sql file execute ( Not Edit )
def execute_sql(CONNECTION, path):
    folder_path = '/'.join(path.split('/')[:-1])
    file = path.split('/')[-1]
    if file in os.listdir(folder_path):
        with psycopg.connect(CONNECTION) as conn:
            conn.execute(open(path, 'r', encoding='utf-8').read())
            conn.commit()
        print("{} EXECUTRED!".format(file))
    else:
        print("{} File Not Exist in {}".format(file, folder_path))
