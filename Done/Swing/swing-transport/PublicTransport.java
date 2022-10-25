public abstract class PublicTransport implements Payable {
    private String model;
    private double baseFare, totalFare;

    public PublicTransport(String model) {
        setModel(model);
    }

    @Override
    public abstract double calculatePayment();

    public String getModel() {
        return this.model;
    }

    public void setModel(String model) {
        this.model = new String(model);
    }

    public double getBaseFare() {
        return this.baseFare;
    }

    public void setBaseFare(double baseFare) {
        this.baseFare = baseFare;
    }

    public double getTotalFare() {
        return this.totalFare;
    }

    public void setTotalFare(double totalFare) {
        this.totalFare = totalFare;
    }
}









