import java.util.Calendar;

public class EBook extends Media {
    private int chapters;

    public EBook(int id, String title, int year, int chapters) {
        super(id, title, year);
        this.chapters = chapters;
    }

    public EBook(String line) {
        super(line);
        chapters = Integer.parseInt(line.substring(line.indexOf("<chapters>") + 10, line.indexOf("</chapters>")));
    }

    public void setChapters(int num) {
        this.chapters = num;
    }

    public int getChapters() {
        return this.chapters;
    }

    public void display() {
        System.out.printf("EBook [ id=%d, title=%s, year=%d, chapters=%d, available=%b ]", super.getID(), super.getTitle(),
                super.getYear(), this.chapters, super.getStatus());
    }

    @Override
    public double calculateRentalFee() {
        int year = Calendar.getInstance().get(Calendar.YEAR);
        if (super.getYear() == year) {
            return (this.chapters * 0.1) + 1;
        }
        return 3.5;
    }

    public String toString() {
        return "<EBook>" + "<id>" + this.getID() + "</id>" + "<title>" + this.getTitle() + "</title>"
                + "<year>" + this.getYear() + "</year>" + "<chapters>" + this.getChapters()
                + "</chapters>" + "<rented>" + this.getStatus() + "</rented>" + "</Ebook>";
    }
}