public class Meter {
    String honorific;
    String firstName;
    String secondName;
    String corporationName;
    String tenetMeterNumber;
    int currentMeterReading;
    String currentMeterReadingDate;
    int previousMeterReading;
    String previousMeterReadingDate;

    public Meter(String[] data) {
        this.honorific = data[0];
        this.firstName = data[1];
        this.secondName = data[2];
        this.corporationName = data[3];
        this.tenetMeterNumber = data[4];
        this.currentMeterReading = Integer.parseInt(data[5]);
        this.currentMeterReadingDate = data[6];
        this.previousMeterReading = Integer.parseInt(data[7]);
        this.previousMeterReadingDate = data[8];
    }
}
