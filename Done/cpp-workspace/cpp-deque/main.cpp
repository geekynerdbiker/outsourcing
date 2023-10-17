#include <iostream>
#include <random>
#include "deque.h"

int main(int argc, const char * argv[]) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis1(0,3);
    uniform_int_distribution<int> dis2(1,13);
    
    Deque dq = Deque();
    
    for (int i = i; i <= 5; i++) {
        int type = dis1(gen) * 13;
        int value = dis2(gen);
        int data = type + value;
        
        cout << "선택된 카드" << i << " : " << dq.dataToString(data) << endl;
        if (dq.isEmpty()) {
            dq.pushFront(data);
            dq.display();
        } else {
            int dir = dq.findDirection(data);
            bool inserted = false;
            

            while (!inserted) {
                if (dir > 0) {
                    dq.insertFront(data, dir);
                    inserted = true;
                }
                else {
                    dq.insertRear(data, dir);
                    inserted = true;
                }
            }
        }
    }
    return 0;
}
