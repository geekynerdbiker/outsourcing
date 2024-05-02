
public class Station {
    private double farePerStation;
    private int nStations;

    public Station(double farePerStation, int nStations) {
        setFarePerStation(farePerStation);
        setNStations(nStations);
    }

    public double getFarePerStation() {
        return this.farePerStation;
    }

    public void setFarePerStation(double farePerStation) {
        this.farePerStation = farePerStation;
    }

    public int getNStations() {
        return this.nStations;
    }

    public void setNStations(int nStations) {
        this.nStations = nStations;
    }
}
