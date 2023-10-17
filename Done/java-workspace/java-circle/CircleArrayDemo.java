public class CircleArrayDemo {
    private Circle [] circleArray;
    String [] colors = {"blue", "red", "yellow"};

    CircleArrayDemo() {
        circleArray = new Circle[10];
        for (int i = 0; i < 10; i++) {
            Die d = new Die();
            d.roll();
            circleArray[i] = new Circle(d.number, colors[d.number % 3]);
        }
    }

    void getCircleArray() {
        for (Circle circle:circleArray) {
            circle.show();
        }
    }

    void randomCompare() {
        Die d = new Die();

        d.roll2();
        int c1 = d.number;

        d.roll2();
        int c2 = d.number;

        System.out.println();
        boolean result = circleArray[c1].sameCircle(circleArray[c2]);
        System.out.print("Circle: ");
        circleArray[c1].show();

        System.out.print("Circle: ");
        circleArray[c2].show();

        System.out.println("is same: " + result);
    }
}
