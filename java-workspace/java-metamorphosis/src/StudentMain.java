import java.util.ArrayList;
import java.util.Scanner;

public class StudentMain {
    public static void main(String[] args) {
        ArrayList<Student> students = new ArrayList<>();

        Student s1 = new Student("Bert Smith", "computing", 21, "12345", true);
        s1.grades.add(new Grade("programming", 52));
        s1.grades.add(new Grade("webdev", 63));
        s1.grades.add(new Grade("maths", 72));
        s1.grades.add(new Grade("algorithms", 68));

        Student s2 = new Student("Olivia Green", "computing", 19, "23464", true);
        s2.grades.add(new Grade("programming", 73));
        s2.grades.add(new Grade("webdev", 82));
        s2.grades.add(new Grade("maths", 72));
        s2.grades.add(new Grade("algorithms", 66));

        Student s3 = new Student("Eloise Jones", "computing", 18, "34744", true);
        s3.grades.add(new Grade("programming", 65));
        s3.grades.add(new Grade("webdev", 63));
        s3.grades.add(new Grade("maths", 37));
        s3.grades.add(new Grade("algorithms", 40));

        Student s4 = new Student("Ben Bird", "computing", 42, "34834", true);
        s4.grades.add(new Grade("programming", 55));
        s4.grades.add(new Grade("webdev", 29));
        s4.grades.add(new Grade("maths", 56));
        s4.grades.add(new Grade("algorithms", 38));

        Student s5 = new Student("Karen Brown", "computing", 25, "45632", true);
        s5.grades.add(new Grade("programming", 62));
        s5.grades.add(new Grade("webdev", 51));
        s5.grades.add(new Grade("maths", 43));
        s5.grades.add(new Grade("algorithms", 43));

        students.add((s1));
        students.add((s2));
        students.add((s3));
        students.add((s4));
        students.add((s5));

        Scanner sc = new Scanner(System.in);

        while (true) {
            System.out.println("1. Report of all students");
            System.out.println("2. All students with a failed module");
            System.out.println("3. Average grade for each student");
            System.out.println("4. Add student");
            System.out.println("0. Exit");
            System.out.print(">> ");

            int command = Integer.parseInt(sc.nextLine());

            if (command == 1) {
                for (Student student : students) {
                    String name = student.getName();
                    String dept = student.getDepartment();
                    String age = Integer.toString(student.getAge());
                    String uname = student.getUserName();
                    String snum = student.getStudentNumber();
                    String ftime = Boolean.toString(student.isFullTime());

                    System.out.printf("%-20s%-15s%-5s%-15s%-10s%-10s\n", "NAME", "DEPT", "AGE", "UNAME", "SNUM", "FTIME");
                    System.out.printf("%-20s%-15s%-5s%-15s%-10s%-10s\n", name, dept, age, uname, snum, ftime);
                    for (int j = 0; j < student.grades.size(); j++) {
                        String subj = student.grades.get(j).getSubject();
                        String score = Character.toString(Grade.getLetterGrade(student.grades.get(j).getScore()));

                        System.out.printf("\t%-15s%-5s\n", subj, score);
                    }
                    System.out.println();
                }
            } else if (command == 2) {
                for (Student student : students) {
                    String name = student.getName();

                    System.out.printf("%-20s\n", name);
                    for (int j = 0; j < student.grades.size(); j++) {
                        String subj = student.grades.get(j).getSubject();
                        String score = Character.toString(Grade.getLetterGrade(student.grades.get(j).getScore()));

                        if (score.compareTo("F") == 0)
                            System.out.printf("\t%-15s%-5s\n", subj, score);
                    }
                    System.out.println();
                }
            } else if (command == 3) {
                for (Student student : students) {
                    String name = student.getName();

                    System.out.printf("%-20s\n", name);
                    double scores = 0;
                    for (int j = 0; j < student.grades.size(); j++)
                        scores += student.grades.get(j).getScore();

                    scores /= student.grades.size();
                    String score = Character.toString(Grade.getLetterGrade(scores));
                    System.out.printf("\t%-10.2f%-5s\n", scores, score);
                    System.out.println();
                }
            } else if (command == 4) {
                System.out.println("Input name:");
                System.out.print(">> ");
                String name = sc.nextLine();

                System.out.println("Input department:");
                System.out.print(">> ");
                String dept = sc.nextLine();

                System.out.println("Input age:");
                System.out.print(">> ");
                int age = Integer.parseInt(sc.nextLine());

                System.out.println("Input student number:");
                System.out.print(">> ");
                String snum = sc.nextLine();

                System.out.println("Input full time (t/f):");
                System.out.print(">> ");
                boolean ftime = sc.nextLine().charAt(0) == 't';

                Student ns = new Student(name, dept, age, snum, ftime);

                for (int i = 0; i < 4; i++) {
                    System.out.println("Input subject:");
                    System.out.print(">> ");
                    String subject = sc.nextLine();

                    System.out.println("Input score:");
                    System.out.print(">> ");
                    double score = Double.parseDouble(sc.nextLine());

                    Grade g = new Grade(subject, score);
                    ns.grades.add(g);
                }
                students.add(ns);
            } else if (command == 0) {
                break;
            } else {
                System.out.println("Invalid command.");
            }
        }
    }
}
