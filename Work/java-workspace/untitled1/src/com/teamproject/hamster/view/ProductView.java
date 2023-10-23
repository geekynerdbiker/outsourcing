package com.teamproject.hamster.view;

import java.util.Scanner;

public class ProductView { // 여기는 일단 예시로 만든것. 로그인페이지에서 넘어가기 테스트 위해서. 다른분들 것 보고 수정할 예정
    Scanner sc = new Scanner(System.in);
    ListView lv = new ListView();

    public void showProductMenu() {
        while (true) {
            System.out.println("상품 목록"); lv.kindOfShoes();
            System.out.println("1. 상품 선택");
            System.out.println("3. 나가기");
            System.out.print("번호 선택: ");
            int num = sc.nextInt();

            switch (num) {
                case 1:

                    System.out.println("ㅇㅇ상품을 선택하셨습니다.");
                    break;
                case 2:

                case 3:
                    return;
                default:
                    System.out.println("잘못된 번호를 입력하셨습니다.");
                    break;
            }
        }
    }
}
