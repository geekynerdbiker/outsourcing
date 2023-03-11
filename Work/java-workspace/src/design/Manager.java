package design;

public class Manager extends Member {
    Manager() {
        super(Position.Manager);
        this.commission = 0.02;
    }

    void addMember(Member m) {
        this.subordinates.add(m);
    }
}
