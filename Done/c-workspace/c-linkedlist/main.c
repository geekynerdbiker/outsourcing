//
//  main.c
//  c-linkedlist
//
//  Created by Jacob An on 2022/04/03.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Listdata {
    char name[30];
    int id;
} listData;

typedef struct Listnode {
    listData data;
    struct Listnode* link;
} listNode;

typedef struct LinkedList {
    listNode* head;
    int length;
} linkedList;

void printList(linkedList* L) {
    listNode* p = L->head;
    
    while (p != NULL) {
        printf("%s %d\n", p->data.name, p->data.id);
        p = p->link;
    }
    printf("\n");
}

void insertLast(linkedList *L, listData item) {
    listNode* p = L->head;
    
    if (p == NULL) {
        listNode* n = (listNode *)malloc(sizeof(listNode));
        n->data = item;
        n->link = NULL;
        L->head = n;
    } else {
        while (p->link != NULL)
            p = p->link;
        
        listNode* n = (listNode *)malloc(sizeof(listNode));
        n->data = item;
        n->link = NULL;
        p->link = n;
    }
    L->length += 1;
}

listNode* search(linkedList* L, int x) {
    listNode* p = L->head;
    
    if (L->length == 0)
        return NULL;
    while (p->link != NULL) {
        if (p->data.id == x)
            return p;
        p = p->link;
    }
    
    return NULL;
}

int insert(linkedList* L, listNode* pre, listData item) {
    listNode* p = search(L, pre->data.id);
    
    if (p != NULL) {
        listNode* n = (listNode *)malloc(sizeof(listNode));
        n->data = item;
        n->link = p->link;
        p->link = n;
        
        L->length += 1;
        printList(L);
        return 1;
    } else
        return 0;
}

int delete(linkedList* L, int x) {
    listNode* p = search(L, x);
    listNode* q = L->head;
    
    while (q->link != p)
        q = q->link;
    
    q->link = p->link;
    free(p);
    
    L->length -= 1;
    printList(L);
    
    return 0;
}

void reverse(linkedList* L) {
    listNode* p, *q, *r;
    p = L->head;
    q = NULL;
    
    while (p != NULL) {
        r = q;
        q = p;
        p = p->link;
        q->link = r;
    }
    L->head = q;
    printList(L);
}

int getLength(linkedList* L) {
    return L->length;
}

int main(int argc, const char * argv[]) {
    FILE *f = fopen("students.txt", "r");
    
    linkedList* L = (linkedList *)malloc(sizeof(linkedList));
    L->head = NULL;
    L->length = 0;
    
    char* line;
    while (fgets(line, 30, f) != NULL) {
        char* ptr = strtok(line, " ");
        
        if (ptr != NULL){
            listData item;
            strcpy(item.name, ptr);
            ptr = strtok(NULL, " ");
            item.id = atoi(ptr);
            insertLast(L, item);
        }
    }
    
    char cmd[50];
    while (true) {
        gets(cmd);
        char* ptr = strtok(cmd, " ");
        
        if (strcmp(ptr, "print") == 0) {
            printList(L);
        } else if (strcmp(ptr, "search") == 0) {
            ptr = strtok(NULL, " ");
            
            if (search(L, atoi(ptr)) == NULL) printf("No such id in the list.\n");
        } else if (strcmp(ptr, "insert") == 0) {
            ptr = strtok(NULL, " ");
            listNode* p = search(L, atoi(ptr));
            
            if (p == NULL) printf("No such id in the list.\n");
            else {
                listData item;
                item.id = atoi(strtok(NULL, ", "));
                strcpy(item.name, strtok(NULL, " "));
                insert(L, p, item);
            }
        } else if (strcmp(ptr, "delete") == 0) {
            ptr = strtok(NULL, " ");
            if (search(L, atoi(ptr)) == NULL) printf("No such id in the list.\n");
            else delete(L, atoi(ptr));
        } else if (strcmp(ptr, "reverse") == 0) {
            reverse(L);
        } else if (strcmp(ptr, "getLength") == 0) {
            printf("Length: %d\n", getLength(L));
        } else if(strcmp(cmd, "exit") == 0) {
            return 0;
        } else {
            printf("Invalid command.\n");
        }
    }
    
    return 0;
}
