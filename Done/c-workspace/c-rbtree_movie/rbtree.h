//
//  rbtree.h
//  c-workspace
//
//  Created by Jacob An on 2023/12/08.
//

#ifndef rbtree_h
#define rbtree_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUM_MOVIES 5
#define NUM_TIMES 5
#define NUM_DAYS 7

#define MAX_SEAT 200
#define MAX_NAME 50
#define MAX_RESERVATION 100

enum Color {
    RED = 0,
    BLACK = 1
};

typedef struct Date{
    int dd;
    int hh;
    int mm;
} Date;

typedef struct Movie{
    char *name;
    char time[10];
    char day[10];
    int seats[MAX_SEAT];
} Movie;

typedef struct Reservation{
    int rid;
    char *name;
    char time[10];
    char day[10];
    int seatNumber;
} Reservation;

typedef struct node {
    int key;
    struct node* left;
    struct node* right;
    struct node* parent;
    enum Color color;
    Reservation* data;
} node;

typedef struct RBTREE {
    node* root;
    node* NIL;
} RBTREE;

node create_nil = {
    .color = BLACK,
    .left = NULL,
    .right = NULL,
    .parent = NULL,
};
node* nil = &create_nil;

typedef struct trunk {
    struct trunk* prev;
    char* str;
} trunk;

bool checkList(int* list, int value);
void del_node(node* n);
void delete_rbtree( RBTREE* tree);
node* newNode(int k, Reservation *rsrv);
RBTREE* newRBtree(void);
node* node_nil(node* x);
node* tree_successor(RBTREE* t, node* n);
node* tree_predeccessor(RBTREE* t, node* n);
void left_Rotate(RBTREE* tree, node* x);
void right_Rotate(RBTREE* tree, node* x);
node* RB_find(RBTREE* tree, int key);
void RB_insert_fixup(RBTREE* tree, node* new_node);
void RB_insert(RBTREE* tree, node* new_node, int k);
void tree_transplant(RBTREE* tree, node* n_1, node* n_2);
void RB_delete_fixup(RBTREE* tree, node* delete_node);
void RB_delete(RBTREE* tree, int k);
node* get_closest(node* n1, node* n2, int k);
node* find_closest(node* n, int k);
void show_trunks(trunk* p);
void Print_BST(node* n, trunk* prev, bool is_left);
void displayRservation(Reservation rsrv[], int count);
void displaySchedule(Movie **sched);
void displaySeat(Movie m);
void makeReservation(RBTREE* tree, Movie **sched, int* count);
void cancelReservation(RBTREE* tree, Reservation rsrv[], int* count);

#endif /* rbtree_h */
