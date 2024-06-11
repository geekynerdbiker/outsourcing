package ajou_service;

import ajou_service.Professor.Professor;
import ajou_service.Student.Student;

import java.io.*;

public class Init {

    public static void initProgram() throws IOException {
        initStudent();
		initProfessor();
		initLecture();
    }

	public static void saveProgram() throws IOException {
		saveStudent();
		saveProfessor();
		saveLecture();
	}

    public static void initStudent() throws IOException {
        File file = new File("data/student.txt");
        if (file.exists()) {
            BufferedReader inFile = new BufferedReader(new FileReader(file));
            String sLine = null;
            String[] token;
            while ((sLine = inFile.readLine()) != null) {
                token = sLine.split(",");
				if (token.length == 3) {
					Management.students.add(new Student(token[0], token[1], token[2]));
				} else if (token.length == 10) {
					Management.students.add(new Student(token[0], token[1], token[2], token[3], token[4], token[5], token[6], token[7], token[8], token[9]));
				} else if (token.length > 3) {
					Management.students.add(new Student(token[0], token[1], token[2]));
				}
            }

        }
    }

    public static void initProfessor() throws IOException {
        File file = new File("data/professor.txt");
        if (file.exists()) {
            BufferedReader inFile = new BufferedReader(new FileReader(file));
            String sLine = null;
            String[] token;
            while ((sLine = inFile.readLine()) != null) {
                token = sLine.split(",");
				if (token.length == 3) {
					Management.professors.add(new Professor(token[0], token[1], token[2]));
				} else if (token.length == 8) {
					Management.professors.add(new Professor(token[0], token[1], token[2], token[3], token[4], token[5], token[6], token[7]));
				} else if (token.length > 3) {
					Management.professors.add(new Professor(token[0], token[1], token[2]));
				}
            }

        }
    }

    public static void initLecture() throws IOException {
        File file = new File("data/lecture.txt");
        if (file.exists()) {
            BufferedReader inFile = new BufferedReader(new FileReader(file));
            String sLine = null;
            String[] token;
            while ((sLine = inFile.readLine()) != null) {
                token = sLine.split(",");
                int index = Management.findProfessor(token[0]);
                Management.professors.get(index).registerLecture(token[1], token[2], token[3]);
            }

        }
    }

	public static void saveStudent() throws IOException {
		File file = new File("data/student2.txt");
		if (file.exists()) {
			BufferedWriter outFile = new BufferedWriter(new FileWriter(file));

			for (Student s: Management.students) {
				outFile.write(s.getName());
				outFile.write(",");
				outFile.write(s.getId());
				outFile.write(",");
				outFile.write(s.getPw());
				outFile.write(",");
				outFile.write(s.getGender());
				outFile.write(",");
				outFile.write(s.getTel());
				outFile.write(",");
				outFile.write(s.getEmail());
				outFile.write(",");
				outFile.write(s.getDepart());
				outFile.write(",");
				outFile.write(s.getSemester());
				outFile.write(",");
				outFile.write(s.getSid());
				outFile.write(",");
				outFile.write(s.getGrade());
				outFile.write("\n");
			}

		}
	}

	public static void saveProfessor() throws IOException {
		File file = new File("data/professor2.txt");
		if (file.exists()) {
			BufferedWriter outFile = new BufferedWriter(new FileWriter(file));

			for (Professor p: Management.professors) {
				outFile.write(p.getName());
				outFile.write(",");
				outFile.write(p.getId());
				outFile.write(",");
				outFile.write(p.getPw());
				outFile.write(",");
				outFile.write(p.getGender());
				outFile.write(",");
				outFile.write(p.getTel());
				outFile.write(",");
				outFile.write(p.getEmail());
				outFile.write(",");
				outFile.write(p.getDepart());
				outFile.write(",");
				outFile.write(p.getSemester());
				outFile.write("\n");
			}

		}
	}

	public static void saveLecture() throws IOException {
		File file = new File("data/lecture2.txt");
		if (file.exists()) {
			BufferedWriter outFile = new BufferedWriter(new FileWriter(file));

			for (Lecture l: Management.lectures) {
				outFile.write(l.getProf());
				outFile.write(",");
				outFile.write(l.getName());
				outFile.write(",");
				outFile.write(l.getTime());
				outFile.write("\n");
			}

		}
	}
}