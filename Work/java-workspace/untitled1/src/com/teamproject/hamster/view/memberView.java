package com.teamproject.hamster.view;

import com.teamproject.hamster.controller.SelectListController;
import com.teamproject.hamster.controller.memberController;
import com.teamproject.hamster.dto.Member;

import java.util.ArrayList;
import java.util.Scanner;

public class memberView {
    public static ArrayList<Member> memberList = new ArrayList<>();

    public void memberView() {


        Scanner sc = new Scanner(System.in);
        memberController s = new memberController();


        while (true) {
            System.out.println("******************************************************");
            System.out.println("1. 로그인  2. 회원가입  3. 마이페이지");
            System.out.println("4. 아이디 찾기  5. 비밀번호 찾기  6. 상품선택  0. 메인페이지로 돌아가기");
            System.out.println("******************************************************");
            System.out.println();
            System.out.print("번호 선택 : ");
            int num = sc.nextInt();

            switch (num) {
                case 1:
                    s.login();
                    continue;
                case 2:
                    s.signUp();
                    continue;
                case 3:
                    s.showMyPage();
                    continue;
                case 4:
                    s.findId();
                    continue;
                case 5:
                    s.findPwd();
                    continue;
//                case 6:
//                    SelectListController myselec = new SelectListController();
//                    myselec.selectMenu();
//                    break;
//                //continue 로 하면 상품선택에서 나가기 하면 다시 여기로 돌아온다.
                case 7:
                    s.print();

                    continue; // 회원 전체정보 조회. 히든으로 7번 지정. 가입 잘 되었나 확인용.
                case 0:
                    System.out.println("메인페이지 이동.");
                    return;
                default:
                    System.out.println("잘못된 번호를 입력하셨습니다.");
                    break;
            }
            break;
        }


    }
}



















