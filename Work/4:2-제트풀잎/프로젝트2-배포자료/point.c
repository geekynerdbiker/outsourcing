#include <stdio.h>
#include <math.h>

typedef struct {
    float x;
    float y;
} point;

point midpoint(point a, point b) {
    point c;
    c.x = (a.x + b.x) / 2.0;
    c.y = (a.y + b.y) / 2.0;
    return c;
}

float distance(point a, point b) {
    float d;
    float dx, dy;
    dx = a.x-b.x;
    dy = a.y-b.y;
    d = sqrt(dx*dx + dy*dy);
    return d;
}

int equal(point a, point b) {
    if ( (a.x==b.x) && (a.y==b.y) ) return 1;
    else return 0;
}

void main() {
    point p1, p2;
    p1.x = 0.0;
    p1.y = 0.0;
    p2.x = 1.0;
    p2.y = 1.0;

    point p3;
    p3 = midpoint(p1,p2);
    printf("%f , %f \n", p3.x, p3.y);

    printf("distance = %f \n", distance(p1,p2));

    if (equal(p1,p2))
        printf("two points are equal \n");
    else
        printf("two points are different \n");

}

