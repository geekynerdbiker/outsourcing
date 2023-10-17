package ajou_service;

import java.util.ArrayList;
import java.util.Scanner;

public class professor extends member{
	private ArrayList<lecture> lectures = new ArrayList<>();
	
	public professor(String name, String id, String pw)
	{
		super(name, id, pw);
	}
	public int get_num_of_lectures()
    {
	    return this.lectures.size();
    }
 
	public lecture get_index_lecture(int index)
	{
     	return lectures.get(index);
	}
	
	public boolean register_lecture(lecture lec) {
		
		if(schedule_check(lec))
		{
			lectures.add(lec);
			management.lectures.add(lec);
			return true;
		}
		return false;
		
	}
	
	public void register_lecture(String lecture_name, String time) {
		
		lecture new_lecture = new lecture(lecture_name, this.get_name(), time);
		if(schedule_check(new_lecture))
		{
			lectures.add(new_lecture);
			management.lectures.add(new_lecture);
		}
			
	}
	
	
	public boolean schedule_check(lecture check)
	{
	
		int time1, time2;
		time1 = check.get_time1();
		time2 = check.get_time2();
		for (lecture temp : this.lectures) {
			
			if(time1 == temp.get_time1() || time1 == temp.get_time2() || time2 == temp.get_time1() || time2 == temp.get_time2())
				return false;
			
		}
		return true;
	}

}
