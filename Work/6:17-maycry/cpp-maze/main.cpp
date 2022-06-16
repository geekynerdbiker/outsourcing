#include <iostream>
#include <time.h>
#include "classes.hpp"
#include "functions.hpp"

int main (){
    // 시작시간 저장
    time_t start = time(NULL);
    int moves = run();
    // 종료시간 저장
    time_t end = time(NULL);
    
    // 소요 시간 및 이동 횟수 출력
    std::cout<<"You won in "<< (double)(end-start)<<" sec\n";
    std::cout<<moves<<" Moves\n";
    return 0;
}
    
