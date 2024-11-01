#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct list {
    Node *head;
    Node *tail;
} List;

int isEmpty(List *l) {
    if (!l->head)
        return 1;
    else
        return 0;
}

void push(List *l, int data) {
    Node *n = (Node *)malloc(sizeof(Node));

    n->data = data;
    n->next = NULL;
    
    if (isEmpty(l)) {
        l->head = n;
        l->tail = n;
    } else {
        l->tail->next = n;
        l->tail = n;
    }
}

int pop(List *l) {
    Node *n;
    int data;
    
    if (isEmpty(l))
        return -1;
    n = l->head;
    data = n->data;
    l->head = l->head->next;
    
    if (!l->head)
        l->tail = l->head;
    
    free(n);
    return data;
}

void set(Node **h, Node **t, int index, int data) {
    Node *n = (Node *)malloc(sizeof(Node));

    n->data = data;
    n->next = NULL;
    
    if (!h[index]) {
        h[index] = (Node *)malloc(sizeof(Node));
        t[index] = (Node *)malloc(sizeof(Node));
        
        h[index] = n;
        t[index] = n;
    } else {
        t[index]->next = n;
        t[index] = n;
    }
}

int get(Node **h, Node **t, int index) {
    Node *n;
    int data;
    
    if (!h[index])
        return -1;
    
    n = h[index];
    data = n->data;
    h[index] = h[index]->next;
    
    if (!h[index])
        t[index] = h[index];
    
    free(n);
    return data;
}

void printList(List *l) {
    Node *p = l->head;
    
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    } printf("\n");
}

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        
        // 1) 4자리 난수 생성 및 정수 저장을 위한 리스트 메모리 할당
        List *list = (List *)malloc(sizeof(List));
        
        srand((unsigned)time(NULL) + i);
        for (int i = 0; i < n; i++) {
            int k =  rand() % 10000;
            push(list, k);
        }
        
        printList(list);
        
        // 2) 0~9 자릿수에 해당하는 연결리스트 10개 생성
        for (int i = 0; i < 10; i++) {
            List *digit = (List *)malloc(sizeof(List));
        }
        
        // 3) 각 연결리스트의 헤드를 저장하는 크기 10의 포인터 배열 생성
        Node *heads[10];
        // 4) 각 연결리스트의 테일을 저장하는 크기 10의 포인터 배열 생성
        Node *tails[10];
        
        int radix, factor = 1;
        for (int i = 0; i < 10; i++) {
            heads[i] = NULL;
            tails[i] = NULL;
        }
        
        for (int pos = 0; pos < 4; pos++) {
            Node *p = list->head;
            
            while (p) {
                radix = (p->data / factor) % 10;
                set(heads, tails, radix, p->data);
                p = p->next;
            }
            
            list = (List *)malloc(sizeof(List));
            for (int i = 0; i < 10; i++) {
                while (heads[i]) {
                    push(list, get(heads, tails, i));
                }
            }
            factor *= 10;
        }
        
        printList(list);
        printf("\n");
    }
    return 0;
}

// 2번 또는 3번 + 4번 둘 중 하나의 자료구조만 있어도 구현이 가능한데 굳이 왜 2가지 다 메모리를 할당해주는지 잘 모르겠음. -> 메모리 낭비
// 2번 선언 및 초기화 할당 후 사용하지 않음.
