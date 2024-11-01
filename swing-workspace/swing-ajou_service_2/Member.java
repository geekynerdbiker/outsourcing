package ajou_service;

public class Member {


    private int type;
    private String name;
    private String id;
    private String pw;
    private String gender;
    private String tel;
    private String email;
    private String depart;
    private String semester;

    public Member(String name, String id, String pw, int type) {
        this.name = name;
        this.id = id;
        this.pw = pw;
        this.type = type;
    }

    public Member(String name, String id, String pw, String gender, String tel, String email, String depart, String semester) {
        this.name = name;
        this.id = id;
        this.pw = pw;
        this.gender = gender;
        this.tel = tel;
        this.email = email;
        this.depart = depart;
        this.semester = semester;
    }
    public int getType() {
        return type;
    }

    public void setType(int type) {
        this.type = type;
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

    public String getPw() {
        return pw;
    }

    public void setPw(String pw) {
        this.pw = pw;
    }

    public String getGender() {
        return gender;
    }

    public void setGender(String gender) {
        this.gender = gender;
    }

    public String getTel() {
        return tel;
    }

    public void setTel(String tel) {
        this.tel = tel;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getDepart() {
        return depart;
    }

    public void setDepart(String depart) {
        this.depart = depart;
    }

    public String getSemester() {
        return semester;
    }

    public void setSemester(String semester) {
        this.semester = semester;
    }

}
