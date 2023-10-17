public class MovieDVD extends Media {
    private double size;

    public MovieDVD(int id, String title, int year, double size) {
        super(id, title, year);
        this.size = size;
    }

    public MovieDVD(String line) {
        super(line);
        size = Double.parseDouble(line.substring(line.indexOf("<size>") + 6, line.indexOf("MB</size>")));
    }

    public double getSize() {
        return this.size;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public void display() {
        System.out.printf("MovieDVD [ id=%d, title=%s, year=%d, size=%.1fMB, available=%b ]", super.getID(),
                super.getTitle(), super.getYear(), this.size, super.getStatus());
    }

    public String toString() {
        return "<MovieDVD>" + "<id>" + this.getID() + "</id>" + "<title>" + this.getTitle() + "</title>"
                + "<year>" + this.getYear() + "</year>" + "<size>" + this.getSize() + "MB</size>"
                + "<rented>" + this.getStatus() + "</rented>" + "</MovieDVD>";
    }
}