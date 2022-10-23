
public class Taxi extends PublicTransport {
    private double farePerKm, distance;

    public Taxi(double baseFare, double farePerKm, double distance) {
        super("KAKAO TAXI");
        super.setBaseFare(baseFare);
        setFarePerKm(farePerKm);
        setDistance(distance);
    }

    @Override
    public double calculatePayment() {
        super.setTotalFare(super.getBaseFare() + getFarePerKm() * getDistance());
        return super.getTotalFare();
    }

    public double getFarePerKm() {
        return this.farePerKm;
    }

    public void setFarePerKm(double farePerKm) {
        this.farePerKm = farePerKm;
    }

    public double getDistance() {
        return this.distance;
    }

    public void setDistance(double distance) {
        this.distance = distance;
    }
}
