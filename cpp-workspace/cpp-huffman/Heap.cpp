#include "Heap.h"
#include <stdexcept>

Heap::Heap(int capacity) : m_capacity(capacity), m_size(0) {
    m_array = new Node * [m_capacity];
}

Heap::~Heap() {
    for (int i = 0; i < m_size; i++) {
        delete m_array[i];
    }
    delete[] m_array;
}

void Heap::push(int m_freq, char m_data) {
    if (m_size == m_capacity) {
        throw std::out_of_range("Heap is full");
    }

    Node* newNode = new Node(m_freq, m_data);
    m_array[m_size] = newNode;
    heapifyUp(m_size);
    m_size++;
}

void Heap::push(Node* node) {
    if (m_size == m_capacity) {
        throw std::out_of_range("Heap is full");
    }
    m_array[m_size] = node;
    heapifyUp(m_size);
    m_size++;
}

Node* Heap::pop() {
    if (isEmpty()) {
        return nullptr;
    }

    Node* root = m_array[0];
    m_size--;
    m_array[0] = m_array[m_size];
    heapifyDown(0);
    return root; 
}

bool Heap::isEmpty() const {
    return m_size == 0;
}

int Heap::size() const {
    return m_size;
}

void Heap::heapifyUp(int idx) {
    while (idx > 0) {
        int parentIdx = (idx - 1) / 2;
        if (m_array[idx]->getFreq() < m_array[parentIdx]->getFreq() ||
           (m_array[idx]->getFreq() == m_array[parentIdx]->getFreq() && m_array[idx]->getData() < m_array[parentIdx]->getData())) {
            Node* temp = m_array[idx];
            m_array[idx] = m_array[parentIdx];
            m_array[parentIdx] = temp;
            idx = parentIdx;
        } else {
            break;
        }
    }
}

void Heap::heapifyDown(int idx) {
    while (true) {
        int leftIdx = 2 * idx + 1;
        int rightIdx = 2 * idx + 2;
        int smallest = idx;

        if (leftIdx < m_size) {
            if (m_array[leftIdx]->getFreq() < m_array[smallest]->getFreq() ||
               (m_array[leftIdx]->getFreq() == m_array[smallest]->getFreq() && m_array[leftIdx]->getData() < m_array[smallest]->getData())) {
                smallest = leftIdx;
            }
        }

        if (rightIdx < m_size) {
            if (m_array[rightIdx]->getFreq() < m_array[smallest]->getFreq() ||
               (m_array[rightIdx]->getFreq() == m_array[smallest]->getFreq() && m_array[rightIdx]->getData() < m_array[smallest]->getData())) {
                smallest = rightIdx;
            }
        }

        if (smallest != idx) {
            Node* temp = m_array[idx];
            m_array[idx] = m_array[smallest];
            m_array[smallest] = temp;
            idx = smallest;
        } else {
            break;
        }
    }
}