import java.util.List;
import java.util.Scanner;
import DB.DAO.*;
import DB.Models.CareerStatistic;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int choice;

        while (true) {
            System.out.println("메뉴:");
            System.out.println("1. 참고도서 조회");
            System.out.println("2. 도서 대출");
            System.out.println("3. 진로통계 조회");
            System.out.println("4. 종료");
            System.out.print("선택: ");
            choice = scanner.nextInt();

            if (choice == 1) {
                System.out.print("수업의 course_id를 입력하세요: ");
                String courseId = scanner.next();
                System.out.print("수업의 sec_id를 입력하세요: ");
                int secId = scanner.nextInt();
                System.out.print("수업의 semester를 입력하세요: ");
                String semester = scanner.next();
                System.out.print("수업의 year를 입력하세요: ");
                int year = scanner.nextInt();

                BookReferenceDAO.getReferenceBooksForCourse(courseId, secId, semester, year);
                break;

            } else if (choice == 2) {
                System.out.print("학번을 입력하세요: ");
                int studentId = scanner.nextInt();

                System.out.print("대출할 도서의 ISBN을 입력하세요: ");
                String bookIsbn = scanner.next();

                BookLoanDAO.borrowBook(studentId, bookIsbn);

            } else if (choice == 3) {
                System.out.print("학과명 입력: ");
                scanner.nextLine();
                String departmentId = scanner.nextLine();
                
                for (int year = 2020; year < 2025; year++) {
                    List<CareerStatistic> stats2 = CareerStatisticDAO.getCareerStatistics(departmentId, year, 2);
                    stats2.forEach(System.out::println);

                    List<CareerStatistic> stats8 = CareerStatisticDAO.getCareerStatistics(departmentId, year, 8);
                    stats8.forEach(System.out::println);
                }

            } else if (choice == 4) {
                System.out.println("종료");
                break;
            }
        }
    }
}


/*
1. 참고도서 예제

1
CS101
1
Fall
2024


2. 도서 대출 예제
(X)
2
3
978-0262033848

(O)
2
1
978-0262033848


3. 진로통계 예제
3
Computer Science

 */