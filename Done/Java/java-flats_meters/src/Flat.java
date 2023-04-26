public class Flat {
    String street;
    int buildingNumber;
    String buildingMeter;
    int currentReading;
    String currentReadingDate;
    int previousReading;
    String previousReadingDate;
    String[] tenetMeters;

    public Flat(String[] data) {
        this.street = data[0];
        this.buildingNumber = Integer.parseInt(data[1]);
        this.buildingMeter = data[2];
        this.currentReading = Integer.parseInt(data[3]);
        this.currentReadingDate = data[4];
        this.previousReading = Integer.parseInt(data[5]);
        this.previousReadingDate = data[6];

        int tenetIndex = data.length - 7;
        this.tenetMeters = new String[tenetIndex];

        for (int i = 7; i < data.length; i++)
            this.tenetMeters[i-7] = data[i];
    }
}
