package com.teamproject.hamster.dto;

public class Member {
    private String name;
    private String id;
    private String pwd;
    private String phone;
    private boolean signUpcoupon;


    public Member() {
    }

    public Member(String id, String pwd){
        this.id = id;
        this.pwd = pwd;
    }

    public Member(String name, String id, String pwd, String phone, boolean signUpcoupon) {
        this.name = name;
        this.id = id;
        this.pwd = pwd;
        this.phone = phone;
        this.signUpcoupon = signUpcoupon;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getPwd() {
        return pwd;
    }

    public void setPwd(String pwd) {
        this.pwd = pwd;
    }

    public String getPhone() {
        return phone;
    }

    public void setPhone(String phone) {
        this.phone = phone;
    }

    public boolean isSignUpcoupon() {
        return signUpcoupon;
    }

    public void setSignUpcoupon(boolean signUpcoupon) {
        this.signUpcoupon = signUpcoupon;
    }

    @Override
    public String toString() {
        return "Member{" +
                "name='" + name + '\'' +
                ", id='" + id + '\'' +
                ", pwd='" + pwd + '\'' +
                ", phone='" + phone + '\'' +
                ", signUpcoupon=" + signUpcoupon +
                '}';
    }
}