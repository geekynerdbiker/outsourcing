public class Bus extends PublicTransport {
    private Station station;

    public Bus(double baseFare, double farePerStation, int nStations) {
        super("KORBUS");
        super.setBaseFare(baseFare);
        setBusStation(farePerStation, nStations);
    }

    @Override
    public double calculatePayment() {
        if (station.getNStations() > 5) {
            super.setTotalFare(super.getBaseFare() + station.getFarePerStation()
                    * (station.getNStations() - 5));
            return super.getTotalFare();
        } else {
            return super.getBaseFare();
        }
    }

    public Station getBusStation() {
        return this.station;
    }

    public void setBusStation(double farePerStation, int nStations) {
        this.station = new Station(farePerStation, nStations);
    }
}
