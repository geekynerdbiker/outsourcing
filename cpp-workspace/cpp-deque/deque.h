#include <string>
#include <iostream>

#ifndef deque_h
#define deque_h

using namespace std;

class Card {
private:
    int data;
    Card* prev;
    Card* next;
    
public:
    Card(const int data, Card* prev = nullptr, Card* next = nullptr) {
        this->data = data;
        if (prev == nullptr && next == nullptr) {
            this->prev = this;
            this->next = this;
        } else {
            this->prev = prev;
            this->next = next;
        }
    }
    
    int getData() const { return data; }
    Card* getPrev() const { return prev; }
    Card* getNext() const { return next; }
    
    void setData(const int data) { this->data = data; }
    void setPrev(Card* c) { this->prev = c; }
    void setNext(Card* c) {this->next = c; }
    
};

class Deque {
private:
    Card* front;
    Card* rear;
    int size;
    
public:
    Deque() {
        front = nullptr;
        rear = nullptr;
        size = 0;
    }
    
    bool isEmpty() const {
        return size == 0;
    }
    
    int getSize() const {
        return size;
    }
    
    int getFront() const {
        return front->getData();
    }
    
    int getRear() const {
        return rear->getData();
    }
    
    void pushFront(const int data) {
        if (isEmpty()) {
            front = rear = new Card(data);
            size++;
            return;
        }
        Card* c = new Card(data, rear, front);
        front->setPrev(c);
        rear->setNext(c);
        front = c;
        size++;
    }
    
    void pushRear(const int data) {
        if (isEmpty()) {
            front = rear = new Card(data);
            size++;
            return;
        }
        Card* c = new Card(data, rear, front);
        front->setPrev(c);
        rear->setNext(c);
        rear = c;
        size++;
    }
    
    void shiftRight() {
        if (isEmpty()) {
            return;
        }
        
        rear = rear->getPrev();
        front = front->getPrev();
    }
    
    void shiftLeft() {
        if (isEmpty()) {
            return;
        }
        
        front = front->getNext();
        rear = rear->getNext();
    }
    
    void display() const {
        if (isEmpty()) return;
        Card* c = front;
        
        for (int i = 0; i < getSize(); i++) {
            cout << dataToString(c->getData()) << " ";
            c = c->getNext();
        }
        cout << endl;
    }
    
    string dataToString(int data) const {
        string type;
        
        if (data / 13 == 0)
            type = "S";
        else if (data / 13 == 1)
            type = "D";
        else if (data / 13 == 2)
            type = "H";
        else if (data / 13 == 3)
            type = "C";
        
        
        string value;
        
        if (data % 13 == 0)
            value = "13";
        else
            value = to_string(data % 13);
        
        return type + value;
    }
    
    int findDirection(int data) const {
        int frontIter = 1, rearIter = -1;
        
        Card *c = front;
        for (int i = 0; i < size && c->getNext() != front; i++) {
            if (c->getData() <= data) {
                frontIter++;
                c = c->getNext();
            }
        }
        
        c = rear;
        for (int i = 0; i < size && c->getPrev() != rear; i++) {
            if (c->getData() <= data) {
                rearIter--;
                c = c->getPrev();
            }
        }
        
        return front >= rear ? frontIter : rearIter;
    }
    
    void insertFront(int data, int iter){
        Card *c = front;
        int frontData = front->getData();
        
        for (int i = 1; i < iter; i++) {
            shiftLeft();
            c = front;
            display();
        }
        
        pushFront(data);
        display();
        
        for (int i = 1; i < iter; i++) {
            shiftRight();
            c = front;
            display();
        }
    }
    
    void insertRear(int data, int iter) {
        Card *c = rear;
        int rearData = rear->getData();
        iter *= -1;
        
        for (int i = 1; i < iter; i++) {
            shiftRight();
            c = rear;
            display();
        }
        
        pushRear(data);
        display();
        
        for (int i = 1; i < iter; i++) {
            shiftLeft();
            c = rear;
            display();
        }
    }
};

#endif /* deque_h */
