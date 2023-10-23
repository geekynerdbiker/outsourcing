package com.teamproject.hamster.run;

import com.teamproject.hamster.controller.CartController;
import com.teamproject.hamster.controller.SelectListController;
import com.teamproject.hamster.dto.ProductDTO;
import com.teamproject.hamster.view.ListView;
import com.teamproject.hamster.view.memberView;

import java.util.ArrayList;
import java.util.Scanner;

public class MainPage {
    public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    while(true){
            memberView mv = new memberView();
            ListView lv = new ListView();
            CartController cartController = new CartController();
            SelectListController mysel = new SelectListController();
            System.out.println("==========================");
            System.out.println("1. 로그인 / 마이페이지");
            System.out.println("2. 상품 목록 보기");
            System.out.println("3. 상품 선택 가기");
            System.out.println("9. 프로그램 종료하기");
            System.out.println("원하시는 페이지를 선택해주세요.");
            int select = sc.nextInt();
            sc.nextLine();
            switch (select){
                case 1 : // 로그인 / 마이페이지
                    mv.memberView();
                    continue;
                case 2 : // 상품목록으로
                    lv.selectList();
                    continue;
                case 3 : // 상품선택으로
                    mysel.selectMenu();
                    continue;
                case 0 : // 프로그램 종료
                    break;
            }
            break;
        }
        System.out.println("프로그램을 종료합니다");
    }
}
