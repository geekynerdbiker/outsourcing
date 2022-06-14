class Circle {
    public final static double PI = 3.141592;
    private double radius;
    private String color;

    Circle() {
        this.radius = 10;
    }

    Circle(double r) {
        this(r, "");
    }

    Circle(double r, String s) {
        this.radius = r;
        this.color = s;
    }

    public void setRadius(double radius) {
        this.radius = radius;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public double getRadius() {
        return this.radius;
    }

    public String getColor() {
        return this.color;
    }

    public boolean sameCircle(Circle o) {
        return this.color.equals(o.getColor()) && this.radius == o.getRadius();
    }

    public void show() {
        System.out.println(radius + " " + color);
    }
}
