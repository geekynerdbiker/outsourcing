#include "Node.h"

class Heap {
private:
    Node** m_array;
    int m_capacity;
    int m_size;

    void heapifyUp(int idx);
    void heapifyDown(int idx);

public:
    Heap(int capacity);
    ~Heap();

    void push(int m_freq, char m_data);
    void push(Node *node);
    Node* pop();
    bool isEmpty() const;
    int size() const;
};
