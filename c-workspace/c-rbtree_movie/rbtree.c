//
//  rbtree.c
//  c-workspace
//
//  Created by Jacob An on 2023/12/08.
//

#include "rbtree.h"

bool checkList(int* list, int value) {
    for (int i = 0; i < 10; i++) {
        if (list[i] == value) {
            return true;
        }
    }
    return false;
}

void del_node(node* n) {
    if (n != NULL) {
        del_node(n->left);
        del_node(n->right);
    }
    free(n);
}

void delete_rbtree(RBTREE* tree) {
    del_node(tree->root);
    free(tree);
}

node* newNode(int k, Reservation *rsrv) {
    node* new = (node*)malloc(sizeof(node));

    new->parent = NULL;
    new->left = NULL;
    new->right = NULL;
    new->key = k;
    new->color = RED;
    new->data = rsrv;

    return new;
}

RBTREE* newRBtree() {
    RBTREE* tree = (RBTREE*)malloc(sizeof(RBTREE));
    node* temp_nil = (node*)malloc(sizeof(node));

    temp_nil->left = NULL;
    temp_nil->right = NULL;
    temp_nil->parent = NULL;
    temp_nil->color = RED;
    temp_nil->data = NULL;

    tree->NIL = temp_nil;

    return tree;
}

node* node_nil(node* x) {
    if (x == NULL) {
        return nil;
    }
    else {
        return x;
    }
}

node* tree_successor(RBTREE* t, node* n) {
    if (n->right != NULL) {
        node* temp_child = n->right;
        while (temp_child->left != NULL) {
            temp_child = temp_child->left;
        }
        return temp_child;
    }
    node* temp_parent = n->parent;
    while (temp_parent != NULL && n == temp_parent->right) {
        n = temp_parent;
        temp_parent = temp_parent->parent;
    }

    return temp_parent;
}

node* tree_predeccessor(RBTREE* t, node* n) {
    if (n->left != NULL) {
        node* temp_child = n->left;
        while (temp_child->right != NULL) {
            temp_child = temp_child->right;
        }
        return temp_child;
    }
    node* temp_parent = n->parent;

    while (temp_parent != NULL && n == temp_parent->left) {
        n = temp_parent;
        temp_parent = temp_parent->parent;
    }

    return temp_parent;
}

void left_Rotate(RBTREE* tree, node* x) {
    node* y = x->right;

    x->right = y->left;

    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        tree->root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void right_Rotate(RBTREE* tree, node* x) {
    node* y = x->left;
    x->left = y->right;

    if (y->right != NULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        tree->root = y;
    }

    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}

node* RB_find(RBTREE* tree, int key) {
    node* temp;
    temp = tree->root;

    while (temp != nil) {
        if (key == temp->key) {
            return temp;
        }
        else if (key > temp->key) {
            temp = temp->right;
        }

        else if (key < temp->key) {
            temp = temp->left;
        }
    }

    return NULL;
}

void RB_insert_fixup(RBTREE* tree, node* new_node) {
    node* y;
    while (new_node->parent != NULL && new_node->parent->color == RED) {
        if (new_node->parent == new_node->parent->parent->left) {
            y = new_node->parent->parent->right;
            
            if (y != NULL && y->color == RED) {
                new_node->parent->color = BLACK;
                y->color = BLACK;
                new_node->parent->parent->color = RED;
                new_node = new_node->parent->parent;
            }
            else {
                if (new_node == new_node->parent->right) {
                    new_node = new_node->parent;
                    left_Rotate(tree, new_node);
                }

                new_node->parent->color = BLACK;
                new_node->parent->parent->color = RED;
                right_Rotate(tree, new_node->parent->parent);
            }
        }
        else {
            y = new_node->parent->parent->left;

            if (y != NULL && y->color == RED) {
                new_node->parent->color = BLACK;
                y->color = BLACK;
                new_node->parent->parent->color = RED;
                new_node = new_node->parent->parent;
            }
            else {
                if (new_node == new_node->parent->left) {
                    new_node = new_node->parent;
                    right_Rotate(tree, new_node);
                }

                new_node->parent->color = BLACK;
                new_node->parent->parent->color = RED;
                left_Rotate(tree, new_node->parent->parent);
            }
        }

    }
    tree->root->color = BLACK;
}

void RB_insert(RBTREE* tree, node* new_node, int k) {
    node* y = tree->NIL;
    node* temp = tree->root;

    if (tree->root == tree->NIL) {
        new_node->color = BLACK;
        tree->root = new_node;
    }
    else {
        while (temp != NULL) {
            y = temp;
            if (k > temp->key) {
                temp = temp->right;
            }
            else {
                temp = temp->left;
            }
        }

        new_node->parent = y;

        if (k > y->key) {
            y->right = new_node;
        }
        else {
            y->left = new_node;
        }

        RB_insert_fixup(tree, new_node);
    }
}

void tree_transplant(RBTREE* tree, node* n_1, node* n_2) {
    if (n_1->parent == NULL) {
        tree->root = n_2;
    }
    else if (n_1 == n_1->parent->left) {
        n_1->parent->left = n_2;
    }
    else {
        n_1->parent->right = n_2;
    }

    if (n_2 != NULL) {
        n_2->parent = n_1->parent;
    }
}

void RB_delete_fixup(RBTREE* tree, node* delete_node) {
    node* s;
    if (delete_node == node_nil(delete_node->parent->left)) {
        s = delete_node->parent->right;
    }
    else {
        s = delete_node->parent->left;
    }
    node* s_left = s->left;
    node* s_right = s->right;
    while (delete_node != tree->root && delete_node->color == BLACK) {
        if (delete_node == node_nil(delete_node->parent->left)) {
            s = delete_node->parent->right;
            if (s->color == RED) {
                s->color = BLACK;
                delete_node->parent->color = RED;
                left_Rotate(tree, delete_node->parent);
                s = delete_node->parent->right;
            }
            s_left = node_nil(s_left);
            s_right = node_nil(s_right);
            if ((s_left->color == BLACK) && (s_right->color == BLACK)) {
                s->color = RED;
                delete_node = delete_node->parent;
            }
            else {
                if (s_right->color == BLACK) {
                    s_left->color = BLACK;
                    s->color = RED;
                    right_Rotate(tree, s);
                    s = delete_node->parent->right;
                }
                s->color = delete_node->parent->color;
                delete_node->parent->color = BLACK;
                s->right->color = BLACK;
                left_Rotate(tree, delete_node->parent);
                delete_node = tree->root;
            }
        }
        else {
            s = delete_node->parent->left;
            if (s->color == RED) {
                s->color = BLACK;
                delete_node->parent->color = RED;
                right_Rotate(tree, delete_node->parent);
                s = delete_node->parent->left;
            }
            s_left = node_nil(s_left);
            s_right = node_nil(s_right);
            if ((s_right->color == BLACK) && (s_left->color == BLACK)) {
                s->color = RED;
                delete_node = delete_node->parent;
            }
            else {
                if (s_left->color == BLACK) {
                    s_right->color = BLACK;
                    s->color = RED;
                    left_Rotate(tree, s);
                    s = delete_node->parent->left;
                }
                s->color = delete_node->parent->color;
                delete_node->parent->color = BLACK;
                s->left->color = BLACK;
                right_Rotate(tree, delete_node->parent);
                delete_node = tree->root;
            }
        }
    }
    delete_node->color = BLACK;
}

void RB_delete(RBTREE* tree, int k) {
    node* delete_node = RB_find(tree, k);

    if (delete_node == NULL) {
        printf("ID가 존재하지 않아 삭제하지 못했습니다.\n");
        return;
    }

    node* y = delete_node;
    node* temp;
    enum Color temp_col = delete_node->color;

    if (delete_node->left == NULL) {
        temp = node_nil(delete_node->right);
        tree_transplant(tree, delete_node, temp);
        free(delete_node);
    }
    else if (delete_node->right == NULL) {
        temp = node_nil(delete_node->left);
        tree_transplant(tree, delete_node, temp);
        free(delete_node);
    }

    else {
        y = tree_successor(tree, delete_node);
        temp_col = y->color;
        temp = node_nil(y->right);


        if (y->parent == delete_node) {
            temp->parent = y;
        }
        else {
            tree_transplant(tree, y, temp);
            y->right = delete_node->right;
            y->right->parent = y;
        }
        tree_transplant(tree, delete_node, y);
        y->left = delete_node->left;
        y->left->parent = y;
        y->color = delete_node->color;
        free(delete_node);
    }

    if (temp_col == BLACK) {
        RB_delete_fixup(tree, temp);
    }

    if (tree->root == nil) {
        tree->root = NULL;
    }
    else if (nil->parent != NULL) {
        if (nil->parent->left == nil) {
            nil->parent->left = NULL;
        }
        else {
            nil->parent->right = NULL;
        }
    }
    nil->parent = NULL;

    printf("ID : %d 삭제 완료\n\n", k);
    
}

node* get_closest(node* n1, node* n2, int k) {
    if (abs(k - n1->key) < abs(k - n2->key)) {
        return n1;
    }
    else {
        return n2;
    }
}

node* find_closest(node* n, int k) {
    if (k < n->key && n->left != NULL) {
        node* temp = find_closest(n->left, k);
        return get_closest(n, temp, k);
    }
    else if (k > n->key && n->right != NULL) {
        node* temp = find_closest(n->right, k);
        return get_closest(n, temp, k);
    }
    else {
        return n;
    }
}

void show_trunks(trunk* p) {
    if (p == NULL) {
        return;
    }
    show_trunks(p->prev);
    printf("%s", p->str);
}

void Print_BST(node* n, trunk* prev, bool is_left) {
    if (n == NULL) {
        return;
    }
    char* prev_str = "    ";

    trunk* trunk_temp = (trunk*)malloc(sizeof(trunk));
    trunk_temp->prev = prev;
    trunk_temp->str = prev_str;

    Print_BST(n->right, trunk_temp, true);

    if (!prev) {
        trunk_temp->str = "---";
    }
    else if (is_left) {
        trunk_temp->str = ",---";
        prev_str = "   |";
    }
    else {
        trunk_temp->str = "`---";
        prev->str = prev_str;
    }
    show_trunks(trunk_temp);
    printf(" %d", n->key);
    if (n->color == RED) {
        printf("%s\n", " R ");
    }
    else {
        printf("%s\n", " B ");
    }

    if (prev) {
        prev->str = prev_str;
    }
    trunk_temp->str = "   |";
    Print_BST(n->left, trunk_temp, false);
}

void displayRservation(Reservation rsrv[], int count) {
    printf("\n==== Current Reservations ====\n");
    for (int i = 0; i < count; i++) {
        if (rsrv[i].rid != -1) {
            printf("Reservation ID: %d\n", rsrv[i].rid);
            printf("Movie: %s\n", rsrv[i].name);
            printf("Time: %s\n", rsrv[i].time);
            printf("Day: %s\n", rsrv[i].day);
            printf("Seat Number: %d\n", rsrv[i].seatNumber);
            printf("\n");
        }
    }
}

void displaySchedule(Movie **sched) {
    printf("\n==== Movie Schedule ====\n");
    for (int i = 0; i < NUM_DAYS; i++) {
        printf("\nDay %d:\n", i + 1);
        for (int j = 0; j < NUM_TIMES; j++) {
            printf("  Time %d: %s\n", j + 1, sched[i][j].name);
        }
    }
}

void displaySeat(Movie m) {
    printf("\n==== Seat Layout for %s ====\n", m.name);
    printf("  Seats: ");
    for (int i = 0; i < MAX_SEAT; i++) {
        if (i % 20 == 0) {
            printf("\n         ");
        }
        printf("%c ", (m.seats[i] == 0) ? 'O' : 'X');
    }
    printf("\n\n");
}

void makeReservation(RBTREE* tree, Movie **sched, int* count) {
    int day, time, seat;
    Reservation *rsrv = (Reservation *)malloc(sizeof(Reservation));
    displaySchedule(sched);
    
    printf("\nEnter the day (1-%d): ", NUM_DAYS);
    scanf("%d", &day);
    printf("Enter the time (1-%d): ", NUM_TIMES);
    scanf("%d", &time);
    
    if (day < 1 || day > NUM_DAYS || time < 1 || time > NUM_TIMES) {
        printf("Invalid day or time. Please try again.\n");
        return;
    }
    
    displaySeat(sched[day - 1][time - 1]);
    
    printf("Enter the seat number (1-%d): ", MAX_SEAT);
    scanf("%d", &seat);
    
    if (seat < 1 || seat > MAX_SEAT || sched[day - 1][time - 1].seats[seat - 1] == 1) {
        printf("Invalid seat or seat already occupied. Please try again.\n");
        return;
    }
    
    rsrv->rid = *count + 1;
    strcpy(rsrv->name, sched[day - 1][time - 1].name);
    strcpy(rsrv->time, sched[day - 1][time - 1].time);
    strcpy(rsrv->day, sched[day - 1][time - 1].day);
    rsrv->seatNumber = seat;
    
    sched[day - 1][time - 1].seats[seat - 1] = 1;
    
    (*count)++;
    
    printf("\nReservation Confirmed!\n");
    printf("Reservation ID: %d\n", rsrv->rid);
    printf("Movie: %s\n", rsrv->name);
    printf("Time: %s\n", rsrv->time);
    printf("Day: %s\n", rsrv->day);
    printf("Seat Number: %d\n", rsrv->seatNumber);
    
    displaySeat(sched[day - 1][time - 1]);
    node *n = newNode(rsrv->rid, rsrv);
    RB_insert(tree, n, rsrv->rid);
}

void cancelReservation(RBTREE* tree, Reservation rsrv[], int* count) {
    int cancelID;
    
    displayRservation(rsrv, *count);
    
    
    int found = 0, i = 0;
    for (i = 0; i < *count; i++) {
        if (rsrv[i].rid == cancelID) {
            rsrv[i].rid = -1;
            found = 1;
            printf("\nReservation Cancelled!\n");
            printf("Cancelled Reservation ID: %d\n", cancelID);
            break;
        }
    }
    
    if (!found) {
        printf("Reservation not found. Please try again.\n");
    }
    RB_delete(tree, rsrv[i].rid);
}
