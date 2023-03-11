package design;
import java.util.ArrayList;

public abstract class Member {
    public Position position;
    public double commission;
    public double salary;
    public ArrayList<Member> subordinates;

    Member(Position position) {
        this.position = position;
        this.salary = 0;
    }

    Position getPosition() { return this.position; }
    ArrayList<Member> getSubordinates() { return this.subordinates; }
}
