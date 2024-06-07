package ajou_service;

import java.io.IOException;
import java.util.Scanner;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

import java.util.ArrayList;

public class management {
	public static ArrayList<student> students = new ArrayList<student>();
	public static ArrayList<professor> professors = new ArrayList<professor>();
	public static ArrayList<lecture> lectures = new ArrayList<lecture>();
	
	public static Scanner scanner = new Scanner(System.in);
	
	public static member now_member;

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		init.Init_Program();
		new LoginScreen();
	}

	public static int find_professor(String name) {
		for (int i = 0; i < professors.size();i++)
			if (professors.get(i).get_name().equals(name))
				return i;
		return -1;
	}
	
}