//
//  main.c
//  c-wordbook
//
//  Created by Jacob An on 2022/06/14.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 256

typedef struct Node {
    char word[64];
    char meaning[128];
    struct Node *left, *right;
} Node;

typedef Node * nodePointer;
FILE *fp;

nodePointer search(nodePointer root, char* word) {
    nodePointer temp = root;

    while (root) {
        temp = root;
        if (strcmp(root->word, word) > 0)
            root = root->left;
        else if (strcmp(root->word, word) < 0)
            root = root->right;
        else {
            return root;
        }
    }
    return temp;
}

int update(Node* root, char* word, char* meaning) {
    Node *ptr = search(root, word);
    
    if (ptr) {
        strcpy(ptr->meaning, meaning);
        return 1;
    }
    return 0;
}

void insert(nodePointer* node, char* word, char* meaning) {
    nodePointer ptr, temp = search(*node, word);

    if (temp || !(*node)) {
        ptr = (nodePointer)malloc(sizeof(*ptr));
        strcpy(ptr->word, word);
        strcpy(ptr->meaning, meaning);
        ptr->left = ptr->right = NULL;

        if (*node) {
            if (strcmp(temp->word, word) > 0)
                temp->left = ptr;
            else
                temp->right = ptr;
        }
        else *node = ptr;
    }
}

void delete(nodePointer* root, char* word) {
    nodePointer parent, ptr, succ, succ_parent, child;
    
    parent = NULL;
    ptr = *root;
    
    while ((ptr != NULL) && strcmp(ptr->word, word) != 0) {
        parent = ptr;
        
        if (strcmp(ptr->word, word) > 0)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    
    if (ptr == NULL) {
        printf("No such word.\n");
        return;
    }
    if ((ptr->left == NULL) && (ptr->right == NULL)) {
        if (parent != NULL) {
            if (parent->left == ptr)
                parent->left = NULL;
            else
                parent->right = NULL;
        }
        else *root = NULL;
    } else if ((ptr->left == NULL) || (ptr->right == NULL)) {
        if (ptr->left != NULL)
            child = ptr->left;
        else
            child = ptr->right;
        
        if (parent != NULL) {
            if (parent->left == ptr)
                parent->left = child;
            else
                parent->right = child;
        }
        else
            *root = child;
    } else {
        succ_parent = ptr;
        succ = ptr->left;
        
        while (succ->right != NULL) {
            succ_parent = succ;
            succ = succ->right;
        }
        
        if (succ_parent->left == succ)
            succ_parent->left = succ->left;
        else
            succ_parent->right = succ->right;
        
        strcpy(ptr->word, succ->word);
        strcpy(ptr->meaning, succ->meaning);
        
        free(ptr);
    }
}



void print(nodePointer root, char* word) {
    Node *ptr = search(root, word);
    
    if (ptr)
        printf("%s: %s\n", ptr->word, ptr->meaning);
    else
        printf("No such word.\n");
    
}

void print_all(nodePointer root) {
    if (root) {
        print_all(root->left);
        printf("%s: %s\n", root->word, root->meaning);
        print_all(root->right);
    }
}

void load(nodePointer* node) {
    char line[MAX_BUFFER_SIZE];
    char *ptrLine;
    
    if (!fp)
        printf("File doesn't exist.\n");
    else {
        while(!feof(fp)) {
            ptrLine = fgets(line, MAX_BUFFER_SIZE, fp);
            if (!ptrLine || strcmp(ptrLine, "\n") == 0)
                break;
            
            char* word = strtok(ptrLine, "\t");
            char* meaning = strtok(NULL, "\t");
            
            if (meaning[strlen(meaning)-1] == '\n')
                meaning[strlen(meaning)-1] = '\0';
            insert(node, word, meaning);
        }
    }
}

void save(nodePointer root) {
    if (root) {
        save(root->left);
        
        fprintf(fp, "%s", root->word);
        fprintf(fp, "\t");
        fprintf(fp, "%s", root->meaning);
        fprintf(fp, "\n");
        
        save(root->right);
    }
}


int main(int argc, const char * argv[]) {
    nodePointer head =  NULL;
    
    fp = fopen("word.txt", "r");;
    load(&head);
    
    int cmd;
    char word[64], meaning[128];
    
    while (1) {
        printf("\n[ 1: ADD, 2: PRINT, 3: PRINT ALL, 4: UPDATE, 5: DELETE 0: EXIT ]\nInput command: ");
        scanf("%d", &cmd);
        
        switch (cmd) {
            case 1:
                printf("Word ? ");
                scanf("%s", word);
                printf("Meaning ? ");
                fflush(stdin);
                fgets(meaning, MAX_BUFFER_SIZE, stdin);
                insert(&head, word, meaning);
                break;
                
            case 2:
                printf("Word ? ");
                scanf("%s", word);
                print(head, word);
                break;
                
            case 3:
                printf("\n[Word List]\n");
                print_all(head);
                break;
                
            case 4:
                printf("Word ? ");
                scanf("%s", word);
                printf("Meaning ? ");
                fflush(stdin);
                fgets(meaning, MAX_BUFFER_SIZE, stdin);
                update(head, word, meaning);
                break;
                
            case 5:
                printf("Word ? ");
                scanf("%s", word);
                delete(&head, word);
                break;
                
            case 0: default:
                fp = fopen("word.txt", "w+");
                save(head);
                fclose(fp);
                return 0;
        }
    }
    return 0;
}

