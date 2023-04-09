package pa1;

public class Ghost extends GameObject {

    private boolean isRest;
    public Ghost(int x, int y) {
        /* add your code, you can add parameter, too */
        setX(x);
        setY(y);
    }

    public void move(int x, int y) {
        /* add your code, you can add parameter, too */
        if (getX() > x) setX(getX() - 1);
        else if (getX() < x) setX(getX() + 1);

        if (getY() > y) setY(getY() - 1);
        else if (getY() < y) setY(getY() + 1);
    }
}