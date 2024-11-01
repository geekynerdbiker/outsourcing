package ajou_service;

import ajou_service.Professor.Professor;
import ajou_service.Student.Student;

import java.io.IOException;

import java.util.ArrayList;

public class Management {
	public static ArrayList<Student> students = new ArrayList<Student>();
	public static ArrayList<Professor> professors = new ArrayList<Professor>();
	public static ArrayList<Lecture> lectures = new ArrayList<Lecture>();
	public static Member currMember;

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		Init.initProgram();
		students.add(new Student("","",""));
		professors.add(new Professor("","",""));
		new Home();
	}

	public static int findProfessor(String name) {
		for (int i = 0; i < professors.size(); i++)
			if (professors.get(i).getName().equals(name))
				return i;
		return -1;
	}
	
}