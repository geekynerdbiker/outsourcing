#include <iostream>
#include <time.h>
#include "classes.hpp"
#include "functions.hpp"

int main (){
    time_t start = time(NULL);
    int moves = run();
    time_t end = time(NULL);
    std::cout<<"You won in "<< (double)(end-start)<<" sec\n";
    return 0;
}
    
