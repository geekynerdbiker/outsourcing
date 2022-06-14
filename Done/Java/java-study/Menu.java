import java.util.*;

public class Menu {

    public static void main(String[] args) {
        String menuNum;
        Management management = new Management();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("[Study Cafe]");
            System.out.println("1.입장");
            System.out.println("2.퇴장");
            System.out.println("3.음식주문");
            System.out.println("4.관리자");
            System.out.println("5.종료");
            System.out.print("--> ");

            menuNum = scanner.next();
            System.out.println();
            switch (menuNum) {
                case "1" -> management.setIn();
                case "2" -> management.setOut();
                case "3" -> management.orderFood();
                case "4" -> management.admin();
                case "5" -> {
                    System.out.println("프로그램이 종료됩니다.");
                    scanner.close();
                    management.scanner.close();
                    management.lineScanner.close();
                    return;
                }
                default -> System.out.println("1, 2, 3, 4 중 하나만 입력해주세요.");
            }
            System.out.println();
        }
    }
}