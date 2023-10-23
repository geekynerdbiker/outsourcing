package com.teamproject.hamster.controller;

import com.teamproject.hamster.dto.Member;
import com.teamproject.hamster.view.MyPage;
import com.teamproject.hamster.view.memberView;

import java.util.Scanner;

import static com.teamproject.hamster.view.memberView.memberList; //memberList.add(newMember); 를 사용하기 위해 임포트

public class memberController {

    private Member logInMember;
    Scanner sc = new Scanner(System.in);

    public boolean signUp() {


        System.out.println("************ 회원가입 ************");
        System.out.print("이름: ");
        String name = sc.next();
        System.out.print("아이디 : ");
        String id = sc.next();
        System.out.print("비밀번호 : ");
        String pwd = sc.next();
        System.out.print("휴대폰 번호 : ");
        String phone = sc.next();


        if(checkId(id)){
            Member newMember = new Member(name, id, pwd, phone, true);
            System.out.println();
            System.out.println("환영합니다! " + id + "님, 가입축하 쿠폰이 발급되었습니다.");
            System.out.println();
            memberList.add(newMember);

            return true;
        } else{

            return false;
        }
    }
    public boolean checkId(String checkId) {

        for (Member m : memberList) {

                if (m.getId().contains(checkId)) { //contains()
                    System.out.println("이미 가입된 회원입니다.");
                    return false;
                }
            }

        return true;
    } //signUp 메소드에서 입력받은 id의 인자를 가져와 equals 검사에 쓸 것이므로
    // 그 id를 매개변수로 받기 위해 String checkId로 매개변수 자리를 만들어주었다.


    public void login () {

        System.out.println("************ 로그인 ************");
        System.out.print("아이디: ");
        String id = sc.next();
        System.out.print("비밀번호: ");
        String pwd = sc.next();
        boolean success = false;

        for (Member user : memberList) { //memberList 배열을 순회하여 Member 객체를 user임시변수에 담아서 처리
//            for (int i = 0; i < memberList.size(); i++) {
//                Member user = memberList.get(i);

                if (user.getId().equals(id)) {
                    if (user.getPwd().equals(pwd)) {
                        System.out.println("안녕하십니까, " + user.getId() + "님");
                        logInMember = user; //현재 로그인한 멤버의 정보를 담아준다. 다른 곳과 구분하기 위해 변수명은 user로 하였다.
                        System.out.println();
                        success = true;
                        //success 변수는 false 이다. 그래서 여기서 true로 바꿔주지않으면
                        //밑의 문장으로 가게 된다. 밑의 문장은 success가 false 일때 실행하는 문장이다.
                    }
                }

        }
        if (!success) {
            System.out.println("아이디 또는 비밀번호가 일치하지 않습니다.");
            System.out.println();
        }
    }

    public void print () {
        for (int i = 0; i < memberList.size(); i++) {
            System.out.println(memberList.get(i));
        }
    }

    //        public void search () {
//            System.out.print("이름을 입력해주세요 : ");
//            String keyword = sc.next();
//            System.out.print("전화번호를 입력해주세요 : ");
//            String keyword2 = sc.next();
//
//            findPwd(keyword, keyword2);
//        }
    public void findPwd (){
        System.out.print("아이디를 입력해주세요 : ");
        String keywordId = sc.next();
        System.out.print("전화번호를 입력해주세요 : ");
        String keywordPhone = sc.next();

        boolean found = false;
        for (Member m : memberList) {

                if (m.getId().equals(keywordId) && m.getPhone().equals(keywordPhone)) {

                    System.out.println(m.getId() + " 님의 비밀번호는 : " + m.getPwd() + " 입니다.");
                    System.out.println();
                    found = true;
                    //배열을 순회하면서 입력값과 일치하는 내용을 찾으면 true로 설정해준다.
                }

        }
        if (!found) { //일치하는 내용이 없다면 그대로 false 이므로 아래를 출력한다.
            System.out.println("입력한 정보와 일치하는 회원을 찾을 수 없습니다.");
            System.out.println();
        }
    }
    public void findId() {

        System.out.print("이름을 입력해주세요 : ");
        String keywordName = sc.next();
        System.out.print("전화번호를 입력해주세요 : ");
        String keywordPhone = sc.next();

        boolean found = false;
        for (Member m : memberList) {

                if (m.getName().equals(keywordName) && m.getPhone().equals(keywordPhone)) {

                    System.out.println(m.getName() + "님의 아이디는 : " + m.getId() + " 입니다.");
                    System.out.println();
                    found = true;
                }

        }
        if (!found) {
            System.out.println("입력한 정보와 일치하는 회원을 찾을 수 없습니다.");
            System.out.println();
        }
    }
//    public void showMyPage() {
//        if (logInMember != null) {
//            System.out.println("마이페이지 정보: " + logInMember.toString());
//        } else {
//            System.out.println("로그인이 필요합니다.");
//        }
//    }

    public void showMyPage() {
        while (true){
        if (logInMember != null) {
            MyPage mp = new MyPage(logInMember);
            System.out.println("1. 이름 수정  2. 비밀번호 수정  3. 휴대폰 번호 수정  4. 내 정보 조회  0. 나가기");
            int choice = sc.nextInt();
            sc.nextLine();

            switch (choice) {
                case 1:
                    System.out.print("이름 수정 : ");
                    String modifyName = sc.nextLine();
                    mp.modifyName(modifyName);
                    continue;
                case 2:
                    System.out.print("비밀번호 수정 : ");
                    String modifyPassword = sc.nextLine();
                    mp.modifyPassword(modifyPassword);
                    continue;
                case 3:
                    System.out.print("휴대폰 번호 수정 : ");
                    String modifyPhone = sc.nextLine();
                    mp.modifyPhone(modifyPhone);
                    continue;
                case 4:
                    System.out.println("내 정보: " + logInMember.toString());
                    continue;
                case 0:
                    System.out.println("마이페이지를 나갑니다.");
                    return;
                default:
                    System.out.println("잘못된 번호를 입력하셨습니다.");
            }
        } else {
            System.out.println("로그인이 필요합니다.");
        }
        break;
    }
    }
}


