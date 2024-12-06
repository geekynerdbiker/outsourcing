CREATE TABLE Student (
    student_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(50) NOT NULL
);

CREATE TABLE Professor (
    professor_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(50) NOT NULL
);

CREATE TABLE Course (
    course_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL
);

CREATE TABLE Classroom (
    classroom_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL
);

CREATE TABLE Timetable (
    timetable_id INT AUTO_INCREMENT PRIMARY KEY,
    course_id INT,
    professor_id INT,
    classroom_id INT,
    day_of_week VARCHAR(10) NOT NULL,
    time_slot VARCHAR(20) NOT NULL,
    FOREIGN KEY (course_id) REFERENCES Course(course_id)
        ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (professor_id) REFERENCES Professor(professor_id)
        ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (classroom_id) REFERENCES Classroom(classroom_id)
        ON DELETE CASCADE ON UPDATE CASCADE,
    UNIQUE(course_id, day_of_week, time_slot)
);

CREATE TABLE Student_Timetable (
    student_id INT,
    timetable_id INT,
    PRIMARY KEY (student_id, timetable_id),
    FOREIGN KEY (student_id) REFERENCES Student(student_id)
        ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (timetable_id) REFERENCES Timetable(timetable_id)
        ON DELETE CASCADE ON UPDATE CASCADE
);

INSERT INTO Professor (name) VALUES
('김재연'), ('김덕령'), ('한범주'), ('김은원'), ('김영선'),
('김도연'), ('안은정'), ('강성인'), ('서상현'), ('조영호'),
('한종훈'), ('강서'), ('이성호'), ('진용일'), ('이수일'),
('김재목'), ('신익조'), ('김영포');

INSERT INTO Classroom (name) VALUES
('창의적강의실1'), ('기기운용'), ('창의적종합'), ('EDA'),
('창의적강의실2'), ('체육 골프연습실(2층)'), ('전산관 합동강의실(2)'),
('다산관 합동강의실(M0502)'), ('IoT창의적'), ('기초회로'),
('통신응용'), ('안테나'), ('창의융합통신강의실1'), ('기초회로실험실'),
('IoT 창의적 종합 설계실'), ('통신응용실험실'), ('안테나 실험실');

INSERT INTO Course (name) VALUES
('직업미래와문제해결'), ('지능형시스템프로젝트'), ('펌웨어 개발'),
('통신특론'), ('전공기초영어2'), ('창업과지적재산권'), ('생활스포츠(골프)'),
('여행과레저'), ('생활속의예술(영화)'), ('인공지능 문제해결프로젝트'),
('파이썬 응용프로그래밍'), ('커뮤니케이션 능력'), ('컴퓨터활용2'),
('스미트기기개론'), ('정보통신기기 아날로그회로설계'), ('스마트기기네트워크'),
('외부평가대비하드웨어개발총론'), ('마이콤응용'), ('전자회로응용'),
('딥러닝프로그래밍'), ('컴퓨터구조'), ('데이터베이스'), ('전자파환경'),
('마이크로파공학');

INSERT INTO Timetable (course_id, professor_id, classroom_id, day_of_week, time_slot)
VALUES
(1, 1, 1, '월', '1-2'),
(2, 2, 2, '월', '2-4'),
(3, 3, 3, '월', '2-4'),
(4, 4, 4, '월', '2-4'),
(5, 1, 1, '월', '3-4'),
(6, 1, 1, '월', '6-7'),
(1, 5, 2, '월', '8-9'),
(3, 3, 3, '월', '6-8'),
(2, 2, 4, '월', '6-8'),
(4, 6, 5, '월', '6-8'),
(7, 7, 6, '화', '2-4'),
(8, 8, 7, '화', '2-4'),
(9, 9, 8, '화', '2-4'),
(10, 10, 9, '화', '2-4'),
(8, 8, 7, '화', '6-8'),
(7, 6, 6, '화', '6-8'),
(10, 10, 9, '화', '6-8'),
(9, 9, 8, '화', '6-8'),
(11, 11, 10, '수', '1-9'),
(12, 12, 11, '수', '2-4'),
(13, 13, 12, '수', '2-4'),
(14, 14, 13, '수', '2-4'),
(12, 12, 11, '수', '2-4'),
(11, 11, 10, '수', '2-4'),
(15, 15, 14, '목', '1-2'),
(16, 16, 15, '목', '2-3'),
(17, 17, 16, '목', '2-3'),
(18, 18, 17, '목', '2-3'),
(19, 19, 18, '목', '2-4'),
(20, 20, 19, '목', '2-4'),
(20, 20, 19, '목', '6-8'),
(19, 19, 18, '목', '6-8'),
(21, 21, 20, '토', '1-2'),
(22, 22, 21, '토', '1-2'),
(23, 23, 22, '토', '3'),
(24, 24, 23, '토', '3'),
(25, 25, 24, '토', '5-6'),
(26, 26, 25, '토', '5-6'),
(27, 27, 26, '토', '7-9'),
(28, 28, 27, '토', '7-9'),
(29, 29, 28, '토', '1-2'),
(30, 30, 29, '토', '1-2'),
(31, 31, 30, '토', '3'),
(32, 32, 31, '토', '3'),
(33, 33, 32, '토', '5-6'),
(34, 34, 33, '토', '5-6'),
(35, 35, 34, '토', '7-9'),
(36, 36, 35, '토', '7-9');
