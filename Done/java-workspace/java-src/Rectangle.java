public class Rectangle implements Comparable<Rectangle> {
    int width, height;
    int x, y;

    Rectangle(int w, int h, int x, int y) {
        width = w;
        height = h;
        this.x = x;
        this.y = y;

    }

    public void location() {
        System.out.println("(" + x + ", " + y + ")");
    }

    public int getSize() {
        return width * height;
    }

    public int overlapArea(Rectangle o) {
        if (x > o.x + o.width) return 0;
        if (x + width < o.x) return 0;
        if (y > o.y + o.height) return 0;
        if (y + height < o.y) return 0;

        int X = Math.max(x, o.x);
        int Y = Math.max(y, o.y);
        int WIDTH = Math.min(x + width, o.x + o.width) - X;
        int HEIGHT = Math.min(y + height, o.y + o.height) - Y;

        return WIDTH * HEIGHT;
    }

    @Override
    public int compareTo(Rectangle o) {
        if (o.width * o.height < width * height)
            return 1;
        else if (o.width * o.height == width * height)
            return 0;
        return -1;
    }
}
