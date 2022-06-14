//
//  main.c
//  c-math
//
//  Created by Jacob An on 2022/04/12.
//

#include <math.h>
#include <stdio.h>
#define PI 3.141592
#define e 0.455

double rad2deg(double r) {
    return r * 180 / PI;
}

double deg2rad(double d) {
    return d * PI / 180;
}

double Qf(double f) {
    double qf = 6571 * pow((1 - 1/(2 * e) * (1 - cos(f))), 1.5);
    
    return isnan(qf) ? 0 : qf;
}

int main(int argc, const char * argv[]) {
    printf("psi\t\t\tcos(psi)\tQ(psi)/N\n");
    
    for (double psi = 0; psi <= 180; psi += 22.5) {
        printf("%.2lf\t\t%.4lf\t\t%.lf\n", psi, cos(deg2rad(psi)), Qf(deg2rad(psi)));
    }
    return 0;
}


