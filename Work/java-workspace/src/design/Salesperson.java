package design;

public class Salesperson extends Member {
    Salesperson() {
        super(Position.Salesperson);
        this.commission = 0.04;
    }
}