import psycopg
from psycopg import sql
# change to your python code file name
from assignment3_code import *

HOST = 'localhost'
DBNAME = 'mydbase'
USER = 'myadmin'
PASSWORD = 'qwer1234'
CONNECTION = f"host={HOST} dbname={DBNAME} user={USER} password={PASSWORD}"

# create table
# change 'my_path' to your path where create_table.sql file exist
path = 'mypath/create_table.sql'

# execute_sql(CONNECTION, path)

# insert_data
# change 'my_path' to your path where insert_data.sql file exist
path = 'mypath/insert_data.sql'

# execute_sql(CONNECTION, path)

# search all data
table_name = 'building'
entire_search(CONNECTION=CONNECTION, table_name=table_name)

# search registration history by student id
student_id = '2017111111'
registration_history(CONNECTION=CONNECTION, student_id=student_id)

# registration course
course_id = 12
student_id = '2022111111'
registration(CONNECTION=CONNECTION, course_id=course_id, student_id=student_id)

# withdrawal course
course_id = 12
student_id = '2022111111'
withdrawal_registration(CONNECTION=CONNECTION, course_id=course_id, student_id=student_id)

# modify lecture room
course_id = 12
buildno = '공D'
roomno = '408'

modify_lectureroom(CONNECTION=CONNECTION, course_id=course_id, buildno=buildno, roomno=roomno)
