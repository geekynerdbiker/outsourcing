//
//  main.cpp
//  cpp-linkedlist
//
//  Created by Jacob An on 2022/04/17.
//

#include <iostream>

using namespace std;

typedef struct Node {
    int data;
    Node* next;
} Node;

Node* head = NULL;

void insert(int data) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;
    
    Node* p = head;
    Node* q = NULL;
    
    if (head == NULL)
        head = n;
    else {
        while (p != NULL) {
            if (p->data > data) {
                if (q == NULL) {
                    n->next = p;
                    head = n;
                } else {
                    n->next = p;
                    q->next = n;
                }
                return;
            }
            q = p;
            p = p->next;
        }
    }
}

int search(int data) {
    Node* p = head;
    
    while (p != NULL) {
        if (p->data == data)
            return 1;
        p = p->next;
    }
    return 0;
}

int remove(int data) {
    Node* p = head;
    Node* q = NULL;
    
    while (p != NULL) {
        if (p->data == data) {
            if (q == NULL)
                head = p->next;
            else {
                q->next = p->next;
                free(p);
                
            }
            return 1;
        }
        q = p;
        p = p->next;
    }
    return 0;
}

void print() {
    Node* p = head;
    
    while (p != NULL) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
};

int main(int argc, const char * argv[]) {
    
    insert(5);
    insert(3);
    insert(4);
    insert(1);
    insert(2);
    remove(3);
    print();
    
    return 0;
}
