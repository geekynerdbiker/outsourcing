package ajou_service;

import java.io.*;

public class init {

    public static void Init_Program() throws IOException {
        init_student();
		init_professor();
		init_lecture();
    }

	public static void Save_Program() throws IOException {
		save_student();
		save_professor();
		save_lecture();
	}

    public static void init_student() throws IOException {
        File file = new File("data/student.txt");
        if (file.exists()) {
            BufferedReader inFile = new BufferedReader(new FileReader(file));
            String sLine = null;
            String[] token;
            while ((sLine = inFile.readLine()) != null) {
                token = sLine.split(",");
                management.students.add(new student(token[0], token[1], token[2]));
            }

        }
    }

    public static void init_professor() throws IOException {
        File file = new File("data/professor.txt");
        if (file.exists()) {
            BufferedReader inFile = new BufferedReader(new FileReader(file));
            String sLine = null;
            String[] token;
            while ((sLine = inFile.readLine()) != null) {
                token = sLine.split(",");
                management.professors.add(new professor(token[0], token[1], token[2]));
            }

        }
    }

    public static void init_lecture() throws IOException {
        File file = new File("data/lecture.txt");
        if (file.exists()) {
            BufferedReader inFile = new BufferedReader(new FileReader(file));
            String sLine = null;
            String[] token;
            while ((sLine = inFile.readLine()) != null) {
                token = sLine.split(",");
                int index = management.find_professor(token[0]);
                management.professors.get(index).register_lecture(token[1], token[2]);
            }

        }
    }

	public static void save_student() throws IOException {
		File file = new File("data/student.txt");
		if (file.exists()) {
			BufferedWriter outFile = new BufferedWriter(new FileWriter(file));

			for (student s: management.students) {
				outFile.write(s.get_name());
				outFile.write(",");
				outFile.write(s.get_id());
				outFile.write(",");
				outFile.write(s.get_pw());
				outFile.write("\n");
			}

		}
	}

	public static void save_professor() throws IOException {
		File file = new File("data/professor.txt");
		if (file.exists()) {
			BufferedWriter outFile = new BufferedWriter(new FileWriter(file));

			for (professor p: management.professors) {
				outFile.write(p.get_name());
				outFile.write(",");
				outFile.write(p.get_id());
				outFile.write(",");
				outFile.write(p.get_pw());
				outFile.write("\n");
			}

		}
	}

	public static void save_lecture() throws IOException {
		File file = new File("data/lecture.txt");
		if (file.exists()) {
			BufferedWriter outFile = new BufferedWriter(new FileWriter(file));

			for (lecture l: management.lectures) {
				outFile.write(l.get_prof());
				outFile.write(",");
				outFile.write(l.get_name());
				outFile.write(",");
				outFile.write(l.get_time());
				outFile.write("\n");
			}

		}
	}
}