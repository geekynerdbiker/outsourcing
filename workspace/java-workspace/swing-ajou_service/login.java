package ajou_service;

public class login {
	
	static String id, pw, name;
	
	public static boolean check_duplicate_id(String id)
	{

		for(int i = 0; i < management.students.size(); i++)
		{
			if(id.equals(management.students.get(i).get_id()))
				return false;
		}
		
		for(int i = 0; i < management.professors.size(); i++)
		{
			if(id.equals(management.professors.get(i).get_id()))
				return false;
		}
		
		return true;
	}
	
	public static member check_id_pw(String id, String pw)
	{
		
		for(int i = 0; i < management.students.size(); i++)
		{
			if(id.equals(management.students.get(i).get_id()) && pw.equals(management.students.get(i).get_pw()))
				return management.students.get(i);
		}
		
		for(int i = 0; i < management.professors.size(); i++)
		{
			if(id.equals(management.professors.get(i).get_id()) && pw.equals(management.professors.get(i).get_pw()))
				return management.professors.get(i);
		}
		
		return null;
		
	}
	
}
