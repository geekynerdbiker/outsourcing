package ajou_service;

import java.util.ArrayList;
import java.util.Scanner;

public class student extends member{
   private ArrayList<lecture> lectures = new ArrayList<>();
   
   public student(String name, String id, String pw)
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
   public boolean register_lecture(lecture lec)
   {
        if(this.duplication_check(lec) && this.schedule_check(lec)) {
           this.lectures.add(lec);
           return true;
        }
        else
        	return false;
  
   }
   public boolean duplication_check(lecture check)
   {
      for(lecture temp : this.lectures)
      {
         if(check == temp)
         {
            System.out.println("�ߺ���û �ϼ̽��ϴ�. Ȯ���Ͻð� �ٽ� ��û�� �ּ���.");
            System.out.println("��ġ�� ������ : " + temp.get_name());
            return false;
         }
         
      }
      return true;
   }
   
   
   public boolean schedule_check(lecture check)
   {
   
      int time1, time2;
      time1 = check.get_time1();
      time2 = check.get_time2();
      for (lecture temp : this.lectures) {
         
         if(time1 == temp.get_time1() || time1 == temp.get_time2() || time2 == temp.get_time1() || time2 == temp.get_time2())
         {
            System.out.println("�ð��� ��ġ�� ������ �����մϴ�. Ȯ���غ��ð� �ٽ� ��û�� �ּ���");
            System.out.println("��ġ�� ������ : " + temp.get_name());
            System.out.println();
            return false;
         }
         
      }
      return true;
   }
   
} 