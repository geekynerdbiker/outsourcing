//
//  main.c
//  c-basic
//
//  Created by Jacob An on 2022/05/06.
//

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct Node* next;
} Node;

void append(Node** Head, Node* NewNode) {
    if ((*Head) == NULL) {
        *Head = NewNode;
    }
    else {
        Node* Tail = (*Head);
        while (Tail->next != NULL) {
            Tail = Tail->next;
        }
        
        Tail->next = NewNode;
    }
}

Node* create(int newData) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = NULL;
    
    return newNode;
}

void removeNode(Node** Head, Node* Remove) {
    if (*Head == Remove) {
            *Head = Remove->next;
        }
        else {
            Node* Current = *Head;
            while (Current != NULL && Current->next != Remove) {
                Current = Current->next;
            }
            if (Current != NULL) {
                Current->next = Remove->next;
            }
        }
}

void removeDuplication(Node *Head) {
    Node *p = Head;
    Node *q = NULL;
    
    while (p != NULL) {
        q = p->next;
        
        while (q != NULL) {
            if (p->data == q->data)
                removeNode(&p, q);
            q = q->next;
        }
        p = p->next;
    }
}

void traverse(Node* Head) {
    Node* n = Head;
    
    while(n != NULL) {
        printf("%d ",n->data);
        n = n->next;
    }
    printf("\n");
}

void reverse(Node **Head) {
    Node* prev = NULL;
        Node* current = *Head;
        Node* next = NULL;
        while (current != NULL) {
            next = current->next;
            current->next = prev;
     
            prev = current;
            current = next;
        }
        *Head = prev;
}


int main(int argc, const char * argv[]) {
    srand((unsigned int)(time(NULL)));
    Node* List = NULL;
    
    for (int i = 0; i < 20; i++)
        append(&List, create(rand() % 50 + 1));
    
    traverse(List);
    removeDuplication(List);
    traverse(List);
    return 0;
}
