package StudyRoom;

import java.text.SimpleDateFormat;

public class Payment {
	static int time_total_Income = 0;
	static int food_total_Income = 0;
	final int FEE_PER_MINUTE = 100;
	final int FEE_PER_HOUR = 5000;
	SimpleDateFormat DateFormat = new SimpleDateFormat("yyyy년 MM월 dd일 HH시 mm분 ss초");
	
	
	int calculateFee(long startTime, long endTime) {
		java.util.Date endDate = new java.util.Date(endTime);
		System.out.println("퇴장시간: " + DateFormat.format(endDate));
		
		int fee = 0;
		long duration = (endTime - startTime) / 1000; //duration : 경과시간, 초 단위
		int hour = (int) (duration / 3600);
		int minute = (int) ((duration % 3600) / 60);
		int second = (int) duration % 60;
		
		System.out.println("사용 시간: " + (hour * 60 + minute) + "분 " + second + "초");
		
		if (second != 0)
			minute++;
		fee = hour * FEE_PER_HOUR + minute * FEE_PER_MINUTE;
		

		return fee;
	}
	
	static int total_Income() {
		return time_total_Income + food_total_Income;
	}
	 
}
