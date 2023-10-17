#include <stdio.h>

int main(int argc, const char * argv[]) {
    double car_speed = 80;
    double time = 6.25;
    
    printf("자동차의 속도는 %.0fkm/h\n", car_speed);
    printf("자동차가 %.2f시간 동안 진행한 거리는 %.2fkm이다.\n", time, time*car_speed);
    
    return 0;
}
