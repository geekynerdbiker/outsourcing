#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

typedef enum { RBTREE_RED, RBTREE_BLACK } color_t;

typedef int key_t;

typedef struct node_t {
    color_t color;
    key_t key;
    struct node_t *parent, *left, *right;
} node_t;

typedef struct tree{
    node_t *root;
    node_t *nil;
} rbtree;

rbtree *new_rbtree(void) {
    rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
    node_t *nilNode = (node_t *)calloc(1, sizeof(node_t));
    
    nilNode->color = RBTREE_BLACK;
    p->nil = nilNode;
    p->root = nilNode;
    
    return p;
}

void right_rotation(rbtree * tree, node_t * x){
    node_t *y;
    
    y = x->left;
    x->left = y->right;
    
    if (y->right != tree->nil)
        y->right->parent = x;
    
    y->parent = x->parent;
    
    if (x->parent == tree->nil)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    
    y->right = x;
    x->parent = y;
}

void left_rotation(rbtree * tree, node_t * x){
    node_t *y;
    
    y = x->right;
    x->right = y->left;
    
    if (y->left != tree->nil)
        y->left->parent = x;
    
    y->parent = x->parent;
    
    if (x->parent == tree->nil)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}

void free_node(rbtree *t, node_t *x) {
    if (x->left != t->nil)
        free_node(t, x->left);
    if (x->right != t->nil)
        free_node(t, x->right);
    
    free(x);
    x = NULL;
}

void delete_rbtree(rbtree *t) {
    if (t->root != t->nil)
        free_node(t, t->root);
    
    free(t->nil);
    free(t);
}

void rbtree_insert_fixup(rbtree *t, node_t *z) {
    node_t *y;
    
    while (z->parent->color == RBTREE_RED) {
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            
            if (y->color == RBTREE_RED) {
                z->parent->color = RBTREE_BLACK;
                y->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotation(t, z);
                }
                z->parent->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                right_rotation(t, z->parent->parent);
            }
        } else {
            y = z->parent->parent->left;
            
            if (y->color == RBTREE_RED) {
                z->parent->color = RBTREE_BLACK;
                y->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotation(t, z);
                }
                z->parent->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                left_rotation(t, z->parent->parent);
            }
        }
    }
    t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
    node_t *y = t->nil;
    node_t *x = t->root;
    node_t *z = (node_t *)calloc(1, sizeof(node_t));
    
    z->key = key;
    
    while (x != t->nil) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    
    z->parent = y;
    
    if (y == t->nil)
        t->root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    
    z->left = t->nil;
    z->right = t->nil;
    z->color = RBTREE_RED;
    
    rbtree_insert_fixup(t, z);
    
    return z;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
    node_t * current = t->root;
    
    while (current != t->nil) {
        if (current->key == key)
            return current;
        if (current->key < key)
            current = current->right;
        else
            current = current->left;
    }
    
    return NULL;
}

node_t *rbtree_min(const rbtree *t) {
    if (t->root == t->nil)
        return NULL;

    node_t * curr = t->root;
    
    while (curr->left != t->nil)
        curr = curr->left;

    return curr;
}

node_t *rbtree_max(const rbtree *t) {
    if (t->root == t->nil)
        return NULL;
    
    node_t * curr = t->root;
    
    while (curr->right != t->nil)
        curr = curr->right;

    return curr;
}

void rbtree_transplant(rbtree *t, node_t * u, node_t * v) {
    if (u->parent == t->nil)
        t->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    
    v->parent = u->parent;
}

void rbtree_delete_fixup(rbtree *t, node_t *x) {
    while (x != t->root && x->color == RBTREE_BLACK) {
        if (x == x->parent->left){
            node_t *w = x->parent->right;
            
            if (w->color == RBTREE_RED){
                w->color = RBTREE_BLACK;
                x->parent->color = RBTREE_RED;
                left_rotation(t, x->parent);
                w = x->parent->right;
            }
            
            if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
                w->color = RBTREE_RED;
                x = x->parent;
            } else {
                if (w->right->color == RBTREE_BLACK) {
                    w->left->color = RBTREE_BLACK;
                    w->color = RBTREE_RED;
                    right_rotation(t, w);
                    w = x->parent->right;
                }
                
                w->color = x->parent->color;
                x->parent->color = RBTREE_BLACK;
                w->right->color = RBTREE_BLACK;
                left_rotation(t, x->parent);
                x = t->root;
            }
        } else {
            node_t *w = x->parent->left;
            
            if (w->color == RBTREE_RED){
                w->color = RBTREE_BLACK;
                x->parent->color = RBTREE_RED;
                right_rotation(t, x->parent);
                w = x->parent->left;
            }
            
            if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) {
                w->color = RBTREE_RED;
                x = x->parent;
            } else {
                if (w->left->color == RBTREE_BLACK) {
                    w->right->color = RBTREE_BLACK;
                    w->color = RBTREE_RED;
                    left_rotation(t, w);
                    w = x->parent->left;
                }
                
                w->color = x->parent->color;
                x->parent->color = RBTREE_BLACK;
                w->left->color = RBTREE_BLACK;
                right_rotation(t, x->parent);
                x = t->root;
            }
        }
    }
    
    x->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *p) {
    node_t *y;
    node_t *x;
    color_t yOriginalColor;
    
    y = p;
    yOriginalColor = y->color;
    
    if (p->left == t->nil)
        x = p->right;
        rbtree_transplant(t, p, p->right);
    else if (p->right == t->nil)
        x = p->left;
        rbtree_transplant(t, p, p->left);
    else {
        y = p->right;
        
        while(y->left != t->nil)
            y = y->left;

        yOriginalColor = y->color;
        x = y->right;
        
        if (y->parent == p)
            x->parent = y;
        else {
            rbtree_transplant(t, y, y->right);
            y->right = p->right;
            y->right->parent = y;
        }
        
        rbtree_transplant(t, p, y);
        y->left = p->left;
        y->left->parent = y;
        y->color = p->color;
    }
    
    if (yOriginalColor == RBTREE_BLACK)
        rbtree_delete_fixup(t, x);
    
    free(p);
    return 0;
}


void _rbtree_print(rbtree * tree, node_t * curr, int tab_count) {
    if (tree->nil == curr)
        return;
    if (tab_count == 1)
        printf("root: %d(%s)\n", curr->key, curr->color == RBTREE_BLACK ? "B" : "R");
    if (curr->left) {
        for (int i = 0; i < tab_count * 4; i++)
            printf(" ");
        printf("left: %d(%s)\n", curr->left->key, curr->left->color == RBTREE_BLACK ? "B" : "R");
        _rbtree_print(tree, curr->left, tab_count+1);
    }
    
    if (curr->right) {
        for (int i = 0; i < tab_count * 4; i++)
            printf(" ");
        printf("right: %d(%s)\n", curr->right->key, curr->right->color == RBTREE_BLACK ? "B" : "R");
        _rbtree_print(tree, curr->right, tab_count+1);
    }
}


void rbtree_print(rbtree * tree) {
    if (!tree->root) {
        printf("empty tree.\n");
        return;
    }
    _rbtree_print(tree, tree->root, 1);
    printf("\n");
}

int main() {
    rbtree *t = new_rbtree();
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 15; i++)
        rbtree_insert(t, rand() % 50);
    rbtree_print(t);
    
    rbtree_insert(t, 12);
    rbtree_insert(t, 15);
    rbtree_insert(t, 41);
    rbtree_insert(t, 43);
    rbtree_insert(t, 5);
    rbtree_print(t);
    
    rbtree_find(t, 9);
    rbtree_find(t, 42);
    rbtree_find(t, 26);
    rbtree_find(t, 3);
    rbtree_find(t, 11);
    rbtree_print(t);
    
    rbtree_erase(t, rbtree_find(t, 15));
    rbtree_erase(t, t->root);
    rbtree_erase(t, rbtree_find(t, 43));
    rbtree_erase(t, rbtree_find(t, 12));
    rbtree_erase(t, t->root);
    rbtree_print(t);
    delete_rbtree(t);
    
    return 0;
}
