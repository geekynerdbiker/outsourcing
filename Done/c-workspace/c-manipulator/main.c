#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.141592

const double a1 = 250, a2 = 200, d4 = 0;
const double t1 = 30, t2 = 15, d3 = 10, t4 = 0;

double degToRad(double n) {
    return n * PI / 180;
}

double radToDeg(double n) {
    return n * 180 / PI;
}

void getT() {
    printf("[T]\n");
    printf("%10.3f%10.3f%10.3f%10.3f\n", cos(degToRad(t1+t2-t4)), sin(degToRad(t1+t2-t4)), 0.0, a1*cos(degToRad(t1))+a2*cos(degToRad(t1+t2)));
    printf("%10.3f%10.3f%10.3f%10.3f\n", sin(degToRad(t1+t2-t4)), -1*cos(degToRad(t1+t2-t4)), 0.0, a1*sin(degToRad(t1))+a2*sin(degToRad(t1+t2)));
    printf("%10.3f%10.3f%10.3f%10.3f\n", 0.0, 0.0, -1.0, -1*(float)(d3+d4));
    printf("%10.3f%10.3f%10.3f%10.3f\n", 0.0, 0.0, 0.0, 1.0);
    
}

void solve1(double *n) {
    double px = a1*cos(degToRad(t1))+a2*cos(degToRad(t1+t2));
    double py = a1*sin(degToRad(t1))+a2*sin(degToRad(t1+t2));
    double D = (pow(px, 2) + pow(py, 2) - pow(a1, 2) - pow(a2, 2)) / (2*a1*a2);
    
    n[1] = radToDeg(atan2(sqrt(1-pow(D, 2)), D));
    n[0] = radToDeg(atan2(py, px) - atan2(a2*sin(degToRad(t2)), a1+a2*cos(degToRad(t2))));
    n[3] = n[0] + n[1] - radToDeg(atan2(sin(degToRad(t1+t2-t4)), cos(degToRad(t1+t2-t4))));
    n[2] = -1 * (-1*(float)(d3+d4)+d4);
    
    for(int i = 0; i < 4; i++)
        printf("%.3lf ", n[i]);
    printf("\n");
}

void solve2(double *n) {
    double px = a1*cos(degToRad(t1))+a2*cos(degToRad(t1+t2));
    double py = a1*sin(degToRad(t1))+a2*sin(degToRad(t1+t2));
    double D = (pow(px, 2) + pow(py, 2) - pow(a1, 2) - pow(a2, 2)) / (2*a1*a2);
    
    n[1] = radToDeg(atan2(-1 * sqrt(1-pow(D, 2)), D));
    n[0] = radToDeg(atan2(py, px) - atan2(a2*sin(degToRad(n[1])), a1+a2*cos(degToRad(n[1]))));
    n[3] = n[0] + n[1] - radToDeg(atan2(sin(degToRad(t1+t2-t4)), cos(degToRad(t1+t2-t4))));
    n[2] = -1 * (-1*(float)(d3+d4)+d4);
    
    for(int i = 0; i < 4; i++)
        printf("%.3lf ", n[i]);
    printf("\n");
}

int main(int argc, const char * argv[]) {
    getT();
    double* result = (double *)malloc(sizeof(double) * 4);
    
    printf("\n[Solve 1]\n");
    solve1(result);
    
    printf("\n[Solve 2]\n");
    solve2(result);
}
