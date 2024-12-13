#include <iostream>

#include "Heap.h"

int main(int argc, char const *argv[]) {
    // expected output"
    // b 2
    // c 5

    Heap queue(10);
    
    queue.push(10, 'a');
    queue.push(2, 'b');
    queue.push(5, 'c');
    queue.push(7, 'd');

    auto top = queue.pop();
    std::cout << top->getData() << " " << top->getFreq() << std::endl;
    delete top;

    top = queue.pop();
    std::cout << top->getData() << " " << top->getFreq() << std::endl;
    delete top;

    return 0;
}