package StudyRoom;

import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.ArrayList;


public class Management {
	private int currentNo;
	ArrayList<Customer> cst = new ArrayList<Customer>(10);
	SeatManage setMan = new SeatManage();
	Payment pay = new Payment();
	String foodList[][] = {{"샌드위치", "5000"}, {"김치볶음밥", "6500"}, {"핫도그", "3000"}, {"아이스아메리카노", "2500"},
							{"콜라, 사이다", "1500"}, {"아이스크림", "1200"}, {"생수", "800"}};
	final int foodName = 0, foodPrice = 1;
	
	
	Management() {
		currentNo = -1;
	}

	void print_menu()
	{
		System.out.println("[LaLaLa StudyRoom]");
		System.out.println("1.입장");
		System.out.println("2.퇴장");
		System.out.println("3.음식주문");
		System.out.println("4.관리자");
		System.out.println("5.종료");
		System.out.print("-->");
		
		Scanner scanner = new Scanner(System.in);
		try
		{
			int num = scanner.nextInt();
			if (num == 1)
				setIn();
			else if (num == 2)
				setOut();	
			else if (num == 3)
				orderFood();
			else if (num == 4)
				admin();
			else if (num == 5)
			{
				scanner.close();
				System.out.println("프로그램을 종료합니다.");
				System.exit(0); //시스템 종료
			}
				
			else
			{
				System.out.println("번호를 잘못 입력하셨습니다.\n");
				print_menu();
			}
		}
		catch(InputMismatchException e)
		{
			System.out.println("번호를 잘못 입력하셨습니다.");
			print_menu();
		}

	}
	
	void setIn() {
		System.out.print("이름을 입력하세요: ");
		Scanner scanner = new Scanner(System.in);
		String name = scanner.next();
		Customer nowCustomer = new Customer(name);
		System.out.println();	
		
		setMan.print();
		System.out.println("\n현재 남은 좌석은 " + setMan.countEmptySeat() + "석 입니다(V: 빈좌석/C:찬좌석).");
		System.out.print("원하는 좌석을 고르세요: ");
		int seatNum = scanner.nextInt();
		if(setMan.setSeat(seatNum/10, seatNum%10))
		{
			System.out.println("선택되었습니다.");
			nowCustomer.seatID = seatNum;
			nowCustomer.startTime = System.currentTimeMillis();
			cst.add(nowCustomer);
			++currentNo;
		}
		print_menu();
	}
	
	void setOut() {
		int seatID = 0;
		int cstIndex = -1;
		while(seatID == 0) {
			System.out.print("이름을 입력하세요: ");
			Scanner scanner = new Scanner(System.in);
			String name = scanner.next();
			for(int i = 0; i < cst.size(); i++) {
				if(name.equals(cst.get(i).name)) {
					seatID = cst.get(i).seatID;
					cstIndex = i;
					break;
				}
			}
			if (seatID == 0) { //입력한 이름과 동일한 이름을 찾을 수 없는 경우
				System.out.println("일치하는 회원을 찾을 수 없습니다. 이름을 다시 입력해주세요.");
			} else
				break;
		}
		System.out.println();	
		System.out.println("당신의 좌석번호는 " + seatID + "입니다.");
		setMan.releaseSeat(seatID / 10, seatID % 10);
		System.out.println("해제되었습니다.");
		currentNo--;
		
		cst.get(cstIndex).calculate();
		
		print_menu();
	}
	
	void admin(){
		System.out.println("[관리자 메뉴]");
		Scanner scanner = new Scanner(System.in);
		int num = -1; 
		while(true) {
			
			System.out.println("1.현재 좌석상태 보기");
			System.out.println("2.전체 좌석 리셋 하기");
			System.out.println("3.손님 현황 보기");
			System.out.println("4.총 수입 확인하기");
			System.out.print("-->");
			System.out.println();
			
			num = scanner.nextInt();
			
			if(num < 5 && num > 0)
				break;
			else {
				System.out.println("번호를 잘못 입력하셨습니다.");
			}
		}
		if(num == 1) {
			System.out.println("[현재 좌석 상태]");
			setMan.print();
			System.out.println("\n찬 좌석: " + (10 - setMan.countEmptySeat()));
			System.out.println("남은 좌석: " + setMan.countEmptySeat());
		}
		else if(num == 2) {
			for(int i = 0; i < cst.size(); i++) {
				cst.get(i).calculate();
			}
			setMan.clear();
			System.out.println("모든 좌석이 해제되었습니다.");
			currentNo = -1;
			cst.clear();
		}
		else if(num == 3) {
			System.out.println("좌석번호\t이름");
			System.out.println("------------");
			for(int i = 0; i < cst.size(); i++)
				System.out.println(cst.get(i).seatID + '\t' + cst.get(i).name);
		}
		else if(num == 4) {
			System.out.println("음식 수입: " + Payment.food_total_Income + "원");
			System.out.println("시간 수입: " + Payment.time_total_Income + "원");
			System.out.println("총 수입: " +  Payment.total_Income() + "원");
		}
		print_menu();
	}

	void orderFood() { 
		int seatID = 0;
		int cstIndex = -1;
		while(seatID == 0) {
			System.out.print("좌석번호를 입력하세요: ");
			Scanner scanner = new Scanner(System.in);
			int temp = scanner.nextInt();
			for(int i = 0; i < cst.size(); i++) {
				if(temp == cst.get(i).seatID) {
					seatID = cst.get(i).seatID;
					cstIndex = i;
					break;
				}
			}
			if (seatID == 0) { //입력한 좌석이 비었을 경우
				System.out.println("빈 좌석입니다. 좌석 번호를 다시 입력해주십시오.");
			} else
				break;
		}
		for(int i = 0; i < 7; i++) {
			System.out.println((i + 1) + ": " + foodList[i][foodName] + '\t' + foodList[i][foodPrice]);
		}
		int total = 0;
		int input;
		while(true) {
			System.out.print("원하는 메뉴의 번호를 한 번에 하나씩입력하세요(그만 주문하시려면 99 입력):");
			Scanner scanner = new Scanner(System.in);
			input = scanner.nextInt();
			if(input < 8 && input > 0) {
				input -= 1; //foodList의 인덱스는 0부터 시작하므로
				System.out.println(foodList[input][foodName] + " 선택: " + foodList[input][foodPrice] + "원");
				total += Integer.parseInt(foodList[input][foodPrice]);
			} else if (input == 99) {
				break;
			} else {
				System.out.println("번호를 잘못 입력하셨습니다. 다시 입력해주십시오.");
			}
		}
		System.out.println("총 금액: " + total + "원");
		cst.get(cstIndex).foodPay += total;
		print_menu();
	}


}