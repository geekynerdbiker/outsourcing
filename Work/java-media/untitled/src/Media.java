public abstract class Media {
    private final int id;
    private String title;
    private int year;
    private boolean available;

    public Media(int id, String title, int year) {
        this.id = id;
        this.title = title;
        this.year = year;
        this.available = true;
    }

    public Media(String line) {
        id = Integer.parseInt(line.substring(line.indexOf("<id>") + 4, line.indexOf("</id>")));
        title = line.substring(line.indexOf("<title>") + 7, line.indexOf("</title>"));
        year = Integer
                .parseInt(line.substring(line.indexOf("<year>") + 15, line.indexOf("</year>")));
        available = Boolean.parseBoolean(line.substring(line.indexOf("<rented>") + 8, line.indexOf("</rented>")));
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setYear(int year) {
        this.year = year;
    }

    public void setStatus(boolean rented) {
        this.available = rented;
    }

    public int getID() {
        return this.id;
    }

    public String getTitle() {
        return this.title;
    }

    public boolean getStatus() {
        return this.available;
    }

    public int getYear() {
        return this.year;
    }

    public double calculateRentalFee() {
        return 3.5;
    }

    protected abstract void display();
}