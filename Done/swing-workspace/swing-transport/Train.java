
public class Train extends PublicTransport {
    private Station station;

    public Train(double baseFare, double farePerStation, int nStations) {
        super("KORAIL");
        super.setBaseFare(baseFare);
        setTrainStation(farePerStation, nStations);
    }

    @Override
    public double calculatePayment() {
        if (station.getNStations() > 5) {
            super.setTotalFare(super.getBaseFare() + (station.getNStations() - 5) * station.getFarePerStation());
            return super.getTotalFare();
        } else return super.getBaseFare();
    }

    public Station getTrainStation() {
        return this.station;
    }

    public void setTrainStation(double farePerStation, int nStation) {
        this.station = new Station(farePerStation, nStation);
    }
}
