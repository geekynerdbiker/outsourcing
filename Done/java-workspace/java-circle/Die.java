import java.util.Random;

class Die {
    int number;
    final int SIDES = 6;

    void roll() {
        Random r = new Random();
        int no = r.nextInt(SIDES);

        this.number = (no % SIDES) + 1;
    }

    void roll2() {
        Random r = new Random();
        int no = r.nextInt(10);

        this.number = (no % 10) + 1;
    }
}
