import java.util.Calendar;

public class MusicCD extends Media {
    private int length;

    public MusicCD(int id, String title, int year, int minutes) {
        super(id, title, year);
        this.length = minutes;
    }

    public MusicCD(String line) {
        super(line);
        length = Integer.parseInt(line.substring(line.indexOf("<length>") + 8, line.indexOf(" minutes</length>")));
    }

    public void setLength(int minutes) {
        this.length = minutes;
    }

    public int getLength() {
        return this.length;
    }

    public void display() {
        System.out.printf("MusicCD [ ID=%d, Title=%s, Year=%d, Length=%dmin ]", super.getID(), super.getTitle(),
                super.getYear(), this.length);
    }

    @Override
    public double calculateRentalFee() {
        int year = Calendar.getInstance().get(Calendar.YEAR);
        if (super.getYear() == year) {
            return (this.length * 0.02) + 1;
        }
        return 3.5;
    }

    public String toString() {
        return "<MusicCD>" + "<id>" + this.getID() + "</id>" + "<title>" + this.getTitle() + "</title>"
                + "<year>" + this.getYear() + "</year>" + "<length>" + this.getLength()
                + " minutes</length>" + "<rented>" + this.getStatus() + "</rented>" + "</MusicCD>";
    }
}