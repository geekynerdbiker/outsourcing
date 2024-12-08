CREATE DATABASE IF NOT EXISTS assignment;
USE assignment;

-- Department 테이블
CREATE TABLE Department (
    dept_name VARCHAR(50) PRIMARY KEY,
    building VARCHAR(50),
    budget DECIMAL
)ENGINE=InnoDB;

-- Instructor 테이블
CREATE TABLE Instructor (
    ID INT PRIMARY KEY,
    name VARCHAR(100),
    salary DECIMAL
)ENGINE=InnoDB;

-- Student 테이블
CREATE TABLE Student (
    ID INT PRIMARY KEY,
    name VARCHAR(100),
    tot_cred INT
)ENGINE=InnoDB;

-- Course 테이블
CREATE TABLE Course (
    course_id VARCHAR(10) PRIMARY KEY,
    title VARCHAR(100),
    credits INT
)ENGINE=InnoDB;

-- Section 테이블
CREATE TABLE Section (
    course_id VARCHAR(10),
    sec_id INT,
    semester VARCHAR(20),
    year INT,
    PRIMARY KEY (course_id, sec_id, semester, year),
    FOREIGN KEY (course_id) REFERENCES Course(course_id)
)ENGINE=InnoDB;


-- Reference Book 테이블
CREATE TABLE Reference_book (
    book_id INT PRIMARY KEY,
    title VARCHAR(100),
    author VARCHAR(100),
    publisher VARCHAR(100),
    publish_year INT,
    ISBN VARCHAR(20)
)ENGINE=InnoDB;

-- Teaches 테이블 (Ternary Relationship)
CREATE TABLE Teaches (
    book_id INT,
    ID INT,  -- Instructor ID
    sec_id INT,
    semester VARCHAR(20),
    year INT,
    PRIMARY KEY (book_id, ID, sec_id, semester, year),
    FOREIGN KEY (book_id) REFERENCES Reference_book(book_id),
    FOREIGN KEY (ID) REFERENCES Instructor(ID)
)ENGINE=InnoDB;

-- Career Statistics 테이블
CREATE TABLE Career_statistic (
    statistic_id INT PRIMARY KEY,
    department_id VARCHAR(50),
    month INT,
    year INT,
    employment INT,
    graduate INT,
    entrepreneurship INT,
    other INT
)ENGINE=InnoDB;

-- Stu Dept 테이블
CREATE TABLE Stu_dept (
    id INT,
    dept_name VARCHAR(50),
    PRIMARY KEY (id),
    FOREIGN KEY (id) REFERENCES Student(ID),
    FOREIGN KEY (dept_name) REFERENCES Department(dept_name)
)ENGINE=InnoDB;

-- Inst Dept 테이블
CREATE TABLE Inst_dept (
    id INT,
    dept_name VARCHAR(50),
    PRIMARY KEY (id),
    FOREIGN KEY (id) REFERENCES Instructor(ID),
    FOREIGN KEY (dept_name) REFERENCES Department(dept_name)
)ENGINE=InnoDB;

-- Course Dept 테이블
CREATE TABLE Course_dept (
    course_id VARCHAR(10),
    dept_name VARCHAR(50),
    PRIMARY KEY (course_id),
    FOREIGN KEY (course_id) REFERENCES Course(course_id),
    FOREIGN KEY (dept_name) REFERENCES Department(dept_name)
)ENGINE=InnoDB;


-- Section / Teaches 사이의 독립성 관리를 위한 트리거
DELIMITER $$

CREATE TRIGGER ValidateTeachesInsert
BEFORE INSERT ON Teaches
FOR EACH ROW
BEGIN
    -- Section 테이블에서 sec_id, semester, year 조합 확인
    IF NOT EXISTS (
        SELECT 1
        FROM Section
        WHERE sec_id = NEW.sec_id
          AND semester = NEW.semester
          AND year = NEW.year
    ) THEN
        CALL RaiseError();
    END IF;
END$$

DELIMITER ;


-- Department 테이블 데이터 추가
INSERT INTO Department (dept_name, building, budget) VALUES
('Computer Science', 'Building A', 1000000),
('Mathematics', 'Building B', 800000),
('Physics', 'Building C', 750000),
('Chemistry', 'Building D', 500000),
('Biology', 'Building E', 250000);

-- Instructor 테이블 데이터 추가
INSERT INTO Instructor (ID, name, salary) VALUES
(1, 'Hong Gildong', 60000),
(2, 'Kim Seojin', 65000),
(3, 'Lee Jiwon', 70000),
(4, 'Park Jiwon', 75000),
(5, 'Choi Hyejin', 68000),
(6, 'Jeong Minseok', 67000),
(7, 'Yoo Seunghwa', 71000),
(8, 'Im Jinhyeok', 72000),
(9, 'Son Jaehyun', 65000),
(10, 'Jang Minyoung', 69000);

-- Student 테이블 데이터 추가
INSERT INTO Student (ID, name, tot_cred) VALUES
(1, 'Kim Jiwon', 30),
(2, 'Lee Haeun', 50),
(3, 'Park Yejin', 45),
(4, 'Jeong Seojin', 60),
(5, 'Choi Minji', 75),
(6, 'Yoo Seungwoo', 80),
(7, 'Im Hojin', 90),
(8, 'Son Taehyun', 40),
(9, 'Jang Nari', 55),
(10, 'Hong Mina', 35),
(11, 'Kim Minseok', 20),
(12, 'Lee Sooyoung', 25),
(13, 'Jeong Hyun', 50),
(14, 'Yoo Hana', 60),
(15, 'Park Taewoo', 70),
(16, 'Choi Kyuhyun', 85),
(17, 'Jang Inseok', 40),
(18, 'Hong Seohyun', 60),
(19, 'Im Suji', 35),
(20, 'Son Haewon', 45),
(21, 'Yoo Jiwon', 55),
(22, 'Kim Yujin', 65),
(23, 'Choi Haejin', 50),
(24, 'Lee Eunbi', 60),
(25, 'Im Solji', 75),
(26, 'Jang Yunseo', 30),
(27, 'Hong Gyuri', 40),
(28, 'Jeong Myungjin', 55),
(29, 'Yoo Soobin', 60),
(30, 'Im Woori', 65);

-- Course 테이블 데이터 추가
INSERT INTO Course (course_id, title, credits) VALUES
('CS101', 'Introduction to Computer Science', 3),
('MATH101', 'Calculus I', 4),
('PHY101', 'Introduction to Physics', 3),
('CHEM101', 'General Chemistry', 3);

-- Section 테이블 데이터 추가
INSERT INTO Section (course_id, sec_id, semester, year) VALUES
('CS101', 1, 'Fall', 2024),
('MATH101', 1, 'Spring', 2024),
('PHY101', 2, 'Fall', 2024),
('CHEM101', 2, 'Spring', 2024);

-- Reference Book 테이블 데이터 추가
INSERT INTO Reference_book (book_id, title, author, publisher, publish_year, ISBN) VALUES
(1, 'Introduction to Algorithms', 'Thomas H. Cormen', 'MIT Press', 2009, '978-0262033848'),
(2, 'Advanced Calculus', 'David V. Widder', 'Dover Publications', 1999, '978-0486601414'),
(3, 'Physics for Scientists and Engineers', 'Raymond A. Serway', 'Cengage Learning', 2013, '978-1133947271'),
(4, 'Chemistry: The Central Science', 'Theodore L. Brown', 'Pearson', 2017, '978-0134414232'),
(5, 'Biology', 'Neil A. Campbell', 'Pearson', 2018, '978-0134728425'),
(6, 'Discrete Mathematics and Its Applications', 'Kenneth H. Rosen', 'McGraw-Hill', 2018, '978-1259676513'),
(7, 'Introduction to Quantum Mechanics', 'David J. Griffiths', 'Pearson', 2017, '978-1107189638'),
(8, 'Organic Chemistry', 'L.G. Wade Jr.', 'Pearson', 2016, '978-0134042282'),
(9, 'Physical Chemistry', 'Peter Atkins', 'Oxford University Press', 2018, '978-0198812261'),
(10, 'The Selfish Gene', 'Richard Dawkins', 'Oxford University Press', 1976, '978-0199291151');

-- Teaches 테이블 데이터 추가
INSERT INTO Teaches (book_id, ID, sec_id, semester, year) VALUES
(1, 1, 1, 'Fall', 2024),
(2, 2, 1, 'Spring', 2024),
(3, 3, 1, 'Fall', 2024),
(4, 4, 1, 'Spring', 2024),
(5, 5, 1, 'Fall', 2024);
(6, 6, 1, 'Fall', 2024),
(7, 7, 1, 'Spring', 2024),
(8, 8, 1, 'Fall', 2024),
(9, 9, 1, 'Spring', 2024),
(10, 10, 1, 'Fall', 2024);

-- Career Statistics 테이블 데이터 추가
INSERT INTO Career_statistic (statistic_id, department_id, month, year, employment, graduate, entrepreneurship, other) VALUES
(1, 'Computer Science', 2, 2023, 50, 200, 10, 5),
(2, 'Computer Science', 8, 2023, 30, 150, 8, 4),
(3, 'Computer Science', 2, 2024, 25, 120, 5, 3),
(4, 'Computer Science', 8, 2024, 20, 100, 4, 2),
(5, 'Mathematics', 2, 2023, 50, 200, 10, 5),
(6, 'Mathematics', 8, 2023, 30, 150, 8, 4),
(7, 'Mathematics', 2, 2024, 25, 120, 5, 3),
(8, 'Mathematics', 8, 2024, 20, 100, 4, 2),
(9, 'Physics', 2, 2023, 50, 200, 10, 5),
(10, 'Physics', 8, 2023, 30, 150, 8, 4),
(11, 'Physics', 2, 2024, 25, 120, 5, 3),
(12, 'Physics', 8, 2024, 20, 100, 4, 2),
(13, 'Chemistry', 2, 2023, 50, 200, 10, 5),
(14, 'Chemistry', 8, 2023, 30, 150, 8, 4),
(15, 'Chemistry', 2, 2024, 25, 120, 5, 3),
(16, 'Chemistry', 8, 2024, 20, 100, 4, 2);

-- Stu Dept 테이블 데이터 추가
INSERT INTO Stu_dept (id, dept_name) VALUES
(1, 'Computer Science'),
(2, 'Mathematics'),
(3, 'Physics'),
(4, 'Chemistry'),
(5, 'Biology'),
(6, 'Computer Science'),
(7, 'Mathematics'),
(8, 'Physics'),
(9, 'Chemistry'),
(10, 'Biology'),
(11, 'Computer Science'),
(12, 'Mathematics'),
(13, 'Physics'),
(14, 'Chemistry'),
(15, 'Biology'),
(16, 'Computer Science'),
(17, 'Mathematics'),
(18, 'Physics'),
(19, 'Chemistry'),
(20, 'Biology'),
(21, 'Computer Science'),
(22, 'Mathematics'),
(23, 'Physics'),
(24, 'Chemistry'),
(25, 'Biology'),
(26, 'Computer Science'),
(27, 'Mathematics'),
(28, 'Physics'),
(29, 'Chemistry'),
(30, 'Biology');

-- Inst Dept 테이블 데이터 추가
INSERT INTO Inst_dept (id, dept_name) VALUES
(1, 'Computer Science'),
(2, 'Mathematics'),
(3, 'Physics'),
(4, 'Chemistry'),
(5, 'Biology'),
(6, 'Computer Science'),
(7, 'Mathematics'),
(8, 'Physics'),
(9, 'Chemistry'),
(10, 'Biology');

-- Course Dept 테이블 데이터 추가
INSERT INTO Course_dept (course_id, dept_name) VALUES
('CS101', 'Computer Science'),
('MATH101', 'Mathematics'),
('PHY101', 'Physics'),
('CHEM101', 'Chemistry');