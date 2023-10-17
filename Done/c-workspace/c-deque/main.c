//
//  main.c
//  c-deque
//
//  Created by Jacob An on 2022/10/10.
//

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef char element;

typedef struct DlistNode {
    element data;
    struct DlistNode *llink;
    struct DlistNode *rlink;
} DlistNode;

typedef struct DequeType {
    int size;
    DlistNode *head;
    DlistNode *tail;
} DequeType;

void error(char *message) {
 fprintf(stderr, "%s\n", message);
 exit(1);
}

void init(DequeType *dq) {
    dq->head = dq->tail = NULL;
    dq->size = 0;
}

DlistNode *create_node(DlistNode *llink, element item, DlistNode *rlink) {
    DlistNode *node = (DlistNode *)malloc(sizeof(DlistNode));
 
    if (node == NULL)
        error("메모리 할당 오류");
    node->llink = llink;
    node->data = item;
    node->rlink = rlink;
 
    return node;
}

int is_empty(DequeType *dq) {
    if (dq->head == NULL)
        return TRUE;
    else
        return FALSE;
}

void add_rear(DequeType *dq, element item) {
    DlistNode *new_node = create_node(dq->tail, item, NULL);
    
    if (is_empty(dq))
        dq->head = dq->tail = new_node;
    else {
        dq->tail->rlink = new_node;
        dq->tail = new_node;
    }
    
    dq->size++;
}

void add_front(DequeType *dq, element item) {
    DlistNode *new_node = create_node(NULL, item, dq->head);
    
    if (is_empty(dq)) {
        dq->head = dq->tail = new_node;
    } else {
        dq->head->llink = new_node;
        dq->head = new_node;
    }
    
    dq->size++;
}

element delete_front(DequeType *dq) {
    element item;
    DlistNode *removed_node;

    if (is_empty(dq))
        error("공백 덱에서 삭제");
    else {
        removed_node = dq->head;
        item = removed_node->data;
        dq->head = dq->head->rlink;
        free(removed_node);
        
        if(dq->head == NULL)
            dq->tail = NULL;
        else
            dq->head->llink = NULL;
    }
    dq->size--;
    
    return item;
}

element delete_rear(DequeType *dq) {
    element item;
    DlistNode *removed_node;

    if (is_empty(dq))
        error("공백 덱에서의 삭제");
    else {
        removed_node = dq->tail;
        item = removed_node->data;
        dq->tail = dq->tail->llink;
        free(removed_node);

        if(dq->tail == NULL)
            dq->head = NULL;
        else
            dq->tail->rlink = NULL;
    }
    dq->size--;
    
    return item;
}

void display(DequeType *dq) {
    DlistNode *p;
    printf("(");
    
    for (p = dq->head; p != NULL; p = p->rlink)
        printf("%d ", p->data);
    printf(")\n");
}

void main() {
    DequeType deque;
    init(&deque);
 
    char *str = (char *)malloc(sizeof(char) * 100);
    
    printf("Input String : ");
    fgets(str, 100, stdin);
    
    for (int i = 0; i < strlen(str); i++) {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
            add_front(&deque, tolower(str[i]));
        else if (str[i] >= '0' && str[i] <= '9')
            add_front(&deque, str[i]);
    }
    
    int result = 0;
    while (deque.size > 1) {
        char a = delete_front(&deque);
        char b = delete_rear(&deque);
        
        if (a == b)
//        if (delete_front(&deque) == delete_rear(&deque))
            result = 1;
        else {
            result = 0;
            break;
        }
    }
    
    if (result)
        printf("TRUE\n");
    else
        printf("FALSE\n");
    
    return;
}
