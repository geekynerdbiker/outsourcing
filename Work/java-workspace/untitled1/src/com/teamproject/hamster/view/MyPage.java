package com.teamproject.hamster.view;

import com.teamproject.hamster.dto.Member;

public class MyPage {
    private Member logInMember;

    public MyPage(Member logInMember) {
        this.logInMember = logInMember;
    } //MyPage 클래스가 Member 객체를 사용하기 위해, 이 생성자에서 Member 타입의 객체를 받아준다.
    //이 생성자는 Member 타입의 매개변수를 받아주고(Member logInMember 를 통해),
    // this 명령어를 통해 이 필드의 loginmember에 객체를 저장해준다.
    //로그인 메소드에서 loginmember 객체를 설정하고, mypage클래스를 생성할 때 이 loginmember 객체를 받아주니까
    //여기서 loginmember 변수를 통해 여러가지로 접근하여 수정하거나 조회할 수 있다.

    public void modifyName(String modifyName) {
        logInMember.setName(modifyName);
        System.out.println("이름이 " + modifyName + " 으로 수정되었습니다.");
    }

    public void modifyPassword(String modifyPassword) {
        logInMember.setPwd(modifyPassword);
        System.out.println("비밀번호가 " + modifyPassword + " 으로 수정되었습니다.");
    }

    public void modifyPhone(String modifyPhone) {
        logInMember.setPhone(modifyPhone);
        System.out.println("휴대폰 번호가 " + modifyPhone + " 으로 수정되었습니다.");
    }



}
