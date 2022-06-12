package StudyRoom;

public class Customer extends Person {
	Customer(String name) {
		super(name);
		seatID = 0;
		startTime = 0;
		endTime = 0;
		foodPay = 0;
		personal = new Payment();
	}
	Payment personal;
	int seatID;
	int foodPay;
	long startTime;
	long endTime;
	
	void calculate() {
		endTime = System.currentTimeMillis();
		int timePay = personal.calculateFee(startTime, endTime);
		System.out.println("시간 사용 요금: " + timePay + "원 ");
		System.out.println("음식 요금: " + foodPay + "원 ");
		int total = foodPay + timePay;
		System.out.println("총 요금: " + total + "원 ");
		Payment.food_total_Income += foodPay;
		Payment.time_total_Income += timePay;
	}
}