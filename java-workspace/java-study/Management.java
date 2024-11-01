import java.util.ArrayList;
import java.util.Calendar;
import java.util.InputMismatchException;
import java.util.Scanner;

public class Management {
    private int currentNo;
    ArrayList<Customer> cst = new ArrayList<>(10);
    SeatManage seatMan = new SeatManage();
    Payment pay = new Payment();
    String[][] foodList;

    Scanner lineScanner = new Scanner(System.in);
    Scanner scanner = new Scanner(System.in);

    Management() {
        currentNo = 0;
        foodList = new String[][]{{"샌드위치", "5000"}, {"김치볶음밥", "6500"}, {"핫도그", "3000"}, {"아이스아메리카노", "2500"}, {"콜라, 사이다", "1500"}, {"아이스크림", "1200"}, {"생수", "800"}};
    }

    void setIn() {
        if (currentNo < 10) {
            System.out.print("이름을 입력하세요: ");
            String name = lineScanner.nextLine();

            for (Customer customer : cst) {
                if (customer.name.equals(name)) {
                    System.out.println("같은 이름이 있습니다. 다른 이름을 입력해주세요.");
                    return;
                }
            }

            seatMan.print();

            System.out.println("현재 남은 좌석은 " + (10 - currentNo) + "석 입니다(V:빈좌석/C:찬좌석).");

            try {
                System.out.print("원하는 좌석을 고르세요: ");
                int seatID = scanner.nextInt();
                int x = seatID / 10 - 1;
                int y = seatID % 10 - 1;

                if (seatMan.setSeat(x, y)) {
                    cst.add(new Customer(name));
                    cst.get(currentNo).seatID = seatID;

                    cst.get(currentNo).startTime = pay.setCheckIn();

                    currentNo++;
                }
            } catch (ArrayIndexOutOfBoundsException e) {
                System.out.println("좌석번호를 잘못 입력하셨습니다.");
            } catch (InputMismatchException e) {
                System.out.println("숫자를 입력해주세요.");
                scanner.next();
            }
        } else
            System.out.println("좌석이 모두 찼습니다.");
    }


    void setOut() {
        if (currentNo == 0)
            System.out.println("좌석이 모두 비어있습니다.");

        else {
            int i;
            System.out.print("이름을 입력하세요: ");
            String name = lineScanner.nextLine();

            for (i = 0; i < cst.size(); i++) {
                if (cst.get(i).name.equals(name)) {
                    System.out.println("당신의 좌석번호는 " + cst.get(i).seatID + "입니다.");

                    int x = cst.get(i).seatID / 10 - 1;
                    int y = cst.get(i).seatID % 10 - 1;
                    seatMan.releaseSeat(x, y);

                    cst.get(i).endTime = pay.setCheckOut();
                    Calendar now = Calendar.getInstance();

                    System.out.println("퇴장 시간: " + now.get(Calendar.YEAR) + "년 " + now.get(Calendar.MONTH) + "월 " + now.get(Calendar.DAY_OF_MONTH) + "일 " + now.get(Calendar.HOUR_OF_DAY) + "시 " + now.get(Calendar.MINUTE) + "분 " + now.get(Calendar.SECOND) + "초");
                    System.out.println("사용 시간: " + (cst.get(i).endTime - cst.get(i).startTime) / 60 + "분" + (cst.get(i).endTime - cst.get(i).startTime) % 60 + "초");
                    System.out.println("시간 사용요금: " + pay.calculateFee(cst.get(i).startTime, cst.get(i).endTime) + "원");
                    System.out.println("음식 요금: " + cst.get(i).foodPay + "원");
                    System.out.println("총 요금: " + (cst.get(i).foodPay + pay.calculateFee(cst.get(i).startTime, cst.get(i).endTime)) + "원");
                    Payment.total_Time_Income += pay.calculateFee(cst.get(i).startTime, cst.get(i).endTime);
                    Payment.total_Food_Income += cst.get(i).foodPay;

                    cst.remove(i);

                    currentNo--;
                    System.out.println("해제되었습니다.");

                    return;
                }
            }
            System.out.println("없는 이름입니다.");
        }
    }


    void admin() {
        System.out.println("1.현재 좌석 상태 보기");
        System.out.println("2.전체 좌석 리셋 하기");
        System.out.println("3.손님 현황 보기");
        System.out.println("4.총 수입 확인하기");
        System.out.print("--> ");

        String adminMenuNum = scanner.next();
        System.out.println();

        switch (adminMenuNum) {
            case "1" -> {
                System.out.println("[현재 좌석 상태]");
                seatMan.print();
                System.out.println("찬 좌석: " + (currentNo));
                System.out.println("남은 좌석: " + (10 - currentNo));
            }
            case "2" -> {
                seatMan.clear();
                cst.clear();
                System.out.println("모든 좌석이 해제되었습니다.");
                currentNo = 0;
            }
            case "3" -> {
                System.out.format("%s\t%s", "좌석번호", "이름");
                System.out.println();
                System.out.println("----------------------------");
                for (Customer customer : cst) {
                    System.out.format("%d\t%s", customer.seatID, customer.name);
                    System.out.println();
                }
            }
            case "4" -> {
                System.out.println("음식 수익: " + Payment.total_Food_Income + "원");
                System.out.println("시간 수익: " + Payment.total_Time_Income + "원");
                System.out.println("총 수익: " + (Payment.total_Time_Income + Payment.total_Food_Income) + "원");
            }
            default -> System.out.println("1, 2, 3, 4 중 하나만 입력해주세요.");
        }
    }

    void orderFood() {
        Customer customer = null;
        try {
            System.out.print("좌석번호를 입력하세요: ");
            int seatID = scanner.nextInt();
            for (Customer value : cst)
                if (value.seatID == seatID)
                    customer = value;
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("좌석번호를 잘못 입력하셨습니다.");
        } catch (InputMismatchException e) {
            System.out.println("숫자를 입력해주세요.");
            scanner.next();
        }
        if (customer == null) {
            System.out.println("없는 번호입니다.");
            return;
        }

        for (int i = 0; i < foodList.length; i++)
            System.out.println((i + 1) + ": " + foodList[i][0] + "\t" + foodList[i][1]);

        while (true) {
            try {
                System.out.print("원하는 메뉴의 번호를 한 번에 하나씩입력하세요(그만 주문하시려면 99 입력):");
                int order = scanner.nextInt();

                if (order == 99) {
                    System.out.println("총 금액: " + customer.foodPay + "원");
                    return;
                }

                System.out.println(foodList[order - 1][0] + " 선택: " + foodList[order - 1][1] + "원");
                customer.foodPay += Integer.parseInt(foodList[order - 1][1]);
            } catch (InputMismatchException e) {
                System.out.println("숫자를 입력해주세요.");
                scanner.next();
            }
        }
    }
}