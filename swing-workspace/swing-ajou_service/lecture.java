package ajou_service;

public class lecture {
	private String lecture_name;
	private String lecture_prof;
	private String lecture_time;
	private int time_num1;
	private int time_num2;
	
	public lecture(String lecture_name, String professor, String time) {
		
		this.lecture_name = lecture_name;
		this.lecture_prof = professor;
		this.lecture_time = time;
		time_num1 = day_to_int(time.substring(0,1)) * 5 + alphabet_to_int(time.substring(1,2));
		time_num2 = day_to_int(time.substring(2,3)) * 5 + alphabet_to_int(time.substring(3,4));
	}

	public String get_name()
	{
		return this.lecture_name;
	}
	public String get_prof()
	{
		return this.lecture_prof;
	}
	public String get_time()
	{
		return this.lecture_time;
	}
	public int get_time1()
	{
		return this.time_num1;
	}
	public int get_time2()
	{
		return this.time_num2;
	}
	
	public static int day_to_int(String day)
	{
		if(day.equals("월"))
			return 0;
		else if(day.equals("화"))
			return 1;
		else if(day.equals("수"))
			return 2;
		else if(day.equals("목"))
			return 3;
		else if(day.equals("금"))
			return 4;
		else
		{
			System.out.println("잘못된 입력입니다. (월~금)으로 입력해주세요");
			return -1;
		}
	}
	public static int alphabet_to_int(String alphabet)
	{
		if(alphabet.equals("A"))
			return 0;
		else if(alphabet.equals("B"))
			return 1;
		else if(alphabet.equals("C"))
			return 2;
		else if(alphabet.equals("D"))
			return 3;
		else if(alphabet.equals("E"))
			return 4;
		else
		{
			System.out.println("잘못된 입력입니다. (A~E)으로 입력해주세요");
			return -1;
		}
	}
}
