#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#pragma warning(disable:4996)

typedef enum { RED, BLACK } nodeColor;

typedef struct rbnode {
    int key;
    nodeColor color;
    struct rbnode* left, * right, * parent;
} rbnode;

rbnode* NIL;

void initNIL() {
    NIL = (rbnode*)malloc(sizeof(rbnode));
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = NULL;
}

void initTree(rbnode** root) {
    initNIL();
    *root = NIL;
}
void leftRotate(rbnode** root, rbnode* x) {
    rbnode* y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rightRotate(rbnode** root, rbnode* x) {
    rbnode* y = x->left;
    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) *root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void insertFixup(rbnode** root, rbnode* z) {
    while (z != *root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            rbnode* y = z->parent->parent->right;
            if (y != NIL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        }
        else {
            rbnode* y = z->parent->parent->left;
            if (y != NIL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

void insert(rbnode** root, rbnode* z) {
    rbnode* y = NIL;
    rbnode* x = *root;

    while (x != NIL) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NIL)
        *root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    z->left = z->right = NIL;
    z->color = RED;

    insertFixup(root, z);
}

void deleteFixup(rbnode** root, rbnode* x) {
    while (x != *root && x != NIL && x->color == BLACK) {
        if (x == x->parent->left) {
            rbnode* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }
        }
        else {
            rbnode* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = BLACK;
}

rbnode* treeMinimum(rbnode* x) {
    while (x!= NIL && x->left != NIL)
        x = x->left;
    return x;
}


void transplant(rbnode** root, rbnode* u, rbnode* v) {
    if (u->parent == NIL) *root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    if (v != NIL) v->parent = u->parent;
}

rbnode* find(rbnode* root, int key) {
    while (root != NIL && key != root->key) {
        if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return root;
}

void delete(rbnode** root, rbnode* z) {
    rbnode* y = z;
    rbnode* x;
    nodeColor yOriginalColor = y->color;

    if (z->left == NIL) {
        x = z->right;
        transplant(root, z, z->right);
    }
    else if (z->right == NIL) {
        x = z->left;
        transplant(root, z, z->left);
    }
    else {
        y = treeMinimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent != z) {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yOriginalColor == BLACK) {
        deleteFixup(root, x);
    }
}

void printInorder(rbnode* root, FILE* fp) {
    if (root != NIL) {
        printInorder(root->left, fp);
        fprintf(fp, "%d ", root->key);
        printInorder(root->right, fp);
    }
}

void printGivenLevel(rbnode* root, int level, FILE* fp) {
    if (root == NIL) return;
    if (level == 1) fprintf(fp, "%d ", root->key);
    else if (level > 1) {
        printGivenLevel(root->left, level - 1, fp);
        printGivenLevel(root->right, level - 1, fp);
    }
}

void printLevelOrder(rbnode* root, FILE* fp) {
    if (root == NIL) return;

    int height = treeHeight(root);
    for (int i = 1; i <= height; i++)
        printGivenLevel(root, i, fp);
}

int treeHeight(rbnode* node) {
    if (node == NIL) return 0;
    else {
        int leftHeight = treeHeight(node->left);
        int rightHeight = treeHeight(node->right);

        if (leftHeight > rightHeight) return (leftHeight + 1);
        else return (rightHeight + 1);
    }
}



int main(int argc, char* argv[]) {
    FILE* f_in = fopen(argv[1], "r");
    FILE* f_out = fopen(argv[2], "w");

    if (!f_in || !f_out) {
        printf("File error.\n");
        return -1;
    }

    rbnode* root = NULL;
    initTree(&root);

    bool is_first_line = true;

    char line[256];
    while (fgets(line, sizeof(line), f_in)) {
        line[strcspn(line, "\n")] = '\0';

        char* token = strtok(line, " ");
        while (token != NULL) {
            int key;
            if (sscanf(token, "%d", &key) == 1) {
                if (is_first_line) {
                    rbnode* node = (rbnode*)malloc(sizeof(rbnode));
                    node->key = key;
                    insert(&root, node);
                }
                else
                    delete(&root, find(root, key));
            }
            token = strtok(NULL, " ");
        }
        printInorder(root, f_out);
        fprintf(f_out, "\n");
        printLevelOrder(root, f_out);
        fprintf(f_out, "\n");

        is_first_line = false;
    }
    fclose(f_in);
    fclose(f_out);

    return 0;
}






