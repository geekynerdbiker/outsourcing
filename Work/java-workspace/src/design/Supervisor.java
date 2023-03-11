package design;

public class Supervisor extends Member {
    Supervisor() {
        super(Position.Supervisor);
        this.commission = 0.03;
    }

    void addMember(Member m) {
        if (m.getPosition() == Position.Manager) return;
        this.subordinates.add(m);
    }
}
