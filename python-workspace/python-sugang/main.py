import mysql.connector

connection = mysql.connector.connect(
    host="localhost",
    user="root",
    password="password",
    database="password"
)

cursor = connection.cursor()

def add_student(student_id, student_name):
    try:
        insert_query = "INSERT INTO Student (student_id, name) VALUES (%s, %s)"
        cursor.execute(insert_query, (student_id, student_name))
        connection.commit()
        return f"학생 {student_name}이(가) 추가되었습니다."
    except Exception as e:
        connection.rollback()
        return f"오류 발생: {e}"

def register_course(student_id, course_id, timetable_id):
    query = """
    SELECT COUNT(*) FROM Student_Timetable
    WHERE student_id = %s AND timetable_id = %s;
    """
    cursor.execute(query, (student_id, timetable_id))
    result = cursor.fetchone()

    if result[0] > 0:
        return "오류: 이미 해당 시간대에 수강신청을 하셨습니다."

    insert_query = """
    INSERT INTO Student_Timetable (student_id, timetable_id)
    VALUES (%s, %s);
    """
    cursor.execute(insert_query, (student_id, timetable_id))
    connection.commit()

    return "수강신청이 완료되었습니다."

def cancel_course(student_id, timetable_id):
    query = """
    SELECT COUNT(*) FROM Student_Timetable
    WHERE student_id = %s AND timetable_id = %s;
    """
    cursor.execute(query, (student_id, timetable_id))
    result = cursor.fetchone()

    if result[0] == 0:
        return "오류: 해당 시간대에 수강신청이 존재하지 않습니다."

    delete_query = """
    DELETE FROM Student_Timetable
    WHERE student_id = %s AND timetable_id = %s;
    """
    cursor.execute(delete_query, (student_id, timetable_id))
    connection.commit()

    return "수강신청이 취소되었습니다."

def view_registered_courses(student_id):
    query = """
    SELECT Course.name, Professor.name AS professor_name, 
           Timetable.day_of_week, Timetable.time_slot, Classroom.name
    FROM Student_Timetable
    JOIN Timetable ON Student_Timetable.timetable_id = Timetable.timetable_id
    JOIN Course ON Timetable.course_id = Course.course_id
    JOIN Professor ON Timetable.professor_id = Professor.professor_id
    JOIN Classroom ON Timetable.classroom_id = Classroom.classroom_id
    WHERE Student_Timetable.student_id = %s;
    """
    cursor.execute(query, (student_id,))
    courses = cursor.fetchall()

    if not courses:
        return "수강한 과목이 없습니다."

    course_list = []
    for course in courses:
        course_list.append(
            f"과목명: {course[0]}, 교수명: {course[1]}, 시간: {course[2]} {course[3]}, 강의실: {course[4]}")

    return "\n".join(course_list)

def student_menu():
    print("=== 학생 수강 신청 시스템 ===")
    print("1. 수강 신청")
    print("2. 수강 취소")
    print("3. 수강 조회")
    print("4. 학생 추가")
    print("9. 종료")

    choice = input("메뉴를 선택하세요: ")

    if choice == "1":
        student_id = int(input("학생 ID를 입력하세요: "))
        course_id = int(input("과목 ID를 입력하세요: "))
        timetable_id = int(input("시간표 ID를 입력하세요: "))
        print(register_course(student_id, course_id, timetable_id))
    elif choice == "2":
        student_id = int(input("학생 ID를 입력하세요: "))
        timetable_id = int(input("취소할 시간표 ID를 입력하세요: "))
        print(cancel_course(student_id, timetable_id))
    elif choice == "3":
        student_id = int(input("학생 ID를 입력하세요: "))
        print(view_registered_courses(student_id))
    elif choice == "4":
        student_id = int(input("학생 ID를 입력하세요: "))
        student_name = input("학생 이름을 입력하세요: ")
        print(add_student(student_id, student_name))
    elif choice == "9":
        print("시스템을 종료합니다.")
        cursor.close()
        connection.close()
        exit()
    else:
        print("잘못된 입력입니다. 다시 시도해주세요.")
    student_menu()

student_menu()
