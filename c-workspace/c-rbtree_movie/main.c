#include "rbtree.h"

RBTREE *t;
trunk *tr;
void insertionTest(void) {
    t = newRBtree();
    
    for (int i = 0; i < 10; i++) {
        Reservation *r = (Reservation *)malloc(sizeof(Reservation));
        
        r->rid = i;
        r->name = (char *)malloc(sizeof(char) * 50);
        strcpy(r->name, "insertion test");
        
        newNode(i, r);
    }
    tr = (trunk *)malloc(sizeof(trunk));
    Print_BST(t->root, tr, true);
}

void deleteionTest(void) {
    for (int i = 0; i < 5; i++)
        RB_delete(t, i);
    tr = (trunk *)malloc(sizeof(trunk));
    Print_BST(t->root, tr, true);
}

Movie **sched;
Reservation *rsrv;

int main(void) {
    insertionTest();
    deleteionTest();
    
    t = newRBtree();
    int command = 0;
    int counter = 0;
    do {
        printf("1. Make Reservations\n");
        printf("2. Cancel Reservations\n");
        
        printf("Input command: ");
        scanf(" %d ", &command);
        
        switch (command) {
            case 1:
                makeReservation(t, sched, &counter);
            case 2:
                cancelReservation(t, rsrv, &counter);
            case 0:
                return 0;
            default:
                printf("Invalid Input.\n");
                break;
                
        }
    } while (1);
    return 0;
}
