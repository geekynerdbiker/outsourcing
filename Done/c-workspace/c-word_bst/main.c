#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _elem {
    char word[10];
    int count;
}element;

struct node {
    struct node * leftChild;
    element data;
    struct node * rightChild;
};

typedef struct node * treePointer;

void inorder(treePointer root) {
    if (root)
    {
        inorder(root->leftChild);
        printf("%s:%d\t", root->data.word, root->data.count);
        inorder(root->rightChild);
    }
}

element* search(treePointer root, char* k) {
    if (!root)
        return NULL;
    if (strcmp(root->data.word, k) == 0)
        return &(root->data);
    if (strcmp(root->data.word, k) > 0)
        return search(root->leftChild, k);
    return search(root->rightChild, k);
}

element* iterSearch(treePointer tree, char* k) {
    while (tree) {
        if (strcmp(tree->data.word, k) == 0)
            return &(tree->data);
        if (strcmp(tree->data.word, k) > 0)
            tree = tree->leftChild;
        else
            tree = tree->rightChild;
    }
    return NULL;
}

treePointer modifiedSearch(treePointer root, char* k) {
    treePointer temp = root;

    while (root) {
        temp = root;
        if (strcmp(root->data.word, k) > 0)
            root = root->leftChild;
        else if (strcmp(root->data.word, k) < 0)
            root = root->rightChild;
        else {
            root->data.count++;
            return NULL;
        }
    }
    return temp;
}

void insertNode(treePointer *node, char* k) {
    treePointer ptr, temp = modifiedSearch(*node, k);

    if (temp || !(*node)) {
        ptr = (treePointer)malloc(sizeof(*ptr));
        strcpy(ptr->data.word, k);
        ptr->data.count = 1;
        ptr->leftChild = ptr->rightChild = NULL;

        if (*node) {
            if (strcmp(temp->data.word, k) > 0)
                temp->leftChild = ptr;
            else
                temp->rightChild = ptr;
        }
        else *node = ptr;
    }
}

int main(void) {
    treePointer root = NULL;

    char input[10];
    
    while (1) {
        printf("next word ? ");
        scanf("%s", input);
        if (strcmp(input, "END") == 0)
            break;
        insertNode(&root, input);
        inorder(root);
        printf("\n");
        
    }
    return 0;
}
