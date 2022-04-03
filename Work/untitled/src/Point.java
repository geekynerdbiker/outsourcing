class Point {
    float x, y;

    Point() { // 매개변수가 없는 생성자. (0, 0)으로 초기화하여 객체 생성.
        this(0, 0);
    } // 빈 객체 (0, 0)으로 초기화 하여 객체 생성.

    Point(float x, float y) { // (x, y)로 초기화하여 객체 생성.
        this.x = x;
        this.y = y;
    }

    // 중점 계산하여 Point 객체로 리턴
    Point midpoint(Point p) { // 중점
        return new Point((float) ((p.x + x) / 2.0), (float) ((p.y + y) / 2.0));
    }

    // 두 점간의 거리 계산
    float distance(Point p) { // 두 점 사이의 거리
        return (float) Math.sqrt(Math.pow((p.x - x), 2) + Math.pow((p.y - y), 2));
    }

    // 서로 같은 점인지 검사
    boolean equals(Point p) { // 두 점이 같은지 검사
        return p.x == x && p.y == y;
    }
}

class TestPoint {
    public static void main(String[] args) {
        Point p1 = new Point(0.0f, 0.0f);
        Point p2 = new Point(1.0f, 1.0f);

        Point p3 = p1.midpoint(p2);
        System.out.println(p3.x + " " + p3.y);
        System.out.println("distance = " + p1.distance(p2));

        if (p1.equals(p2))
            System.out.println("two points are equal ");
        else
            System.out.println("two points are different ");
    }
}
