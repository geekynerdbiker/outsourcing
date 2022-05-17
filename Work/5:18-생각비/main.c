#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node Node;
struct node {
    int data;
    Node *prev, *next;
};

Node *head = NULL;

int hasDuplication(int data) {
    Node *p = head;
    if (head == NULL) return 0;
    else {
        while (p != NULL) {
            if (p->data == data) return 1;
            p = p->next;
        }
    }
    return 0;
}

int insert(int data) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = data;
    n->prev = NULL;
    n->next = NULL;
    
    if (!hasDuplication(data)) {
        Node *p = head;
        if (head == NULL) {
            head = n;
            return 1;
        } else {
            while (p->next != NULL) {
                if (p->next->data < data) p = p->next;
                else break;
            }
            if (p == head) {
                if (p->data > data) {
                    head = n;
                    n->next = p;
                    p->prev = n;
                    return 1;
                } else {
                    n->next = p->next;
                    n->prev = p;
                    p->next->prev = n;
                    p->next = n;
                    return 1;
                }
            } else if (p->next == NULL) {
                if (p->data < data) {
                    p->next = n;
                    n->prev = p;
                    return 1;
                } else {
                    n->next = p->next;
                    n->prev = p;
                    p->next->prev = n;
                    p->next = n;
                    return 1;
                }
            } else {
                n->next = p->next;
                n->prev = p;
                p->next->prev = n;
                p->next = n;
                return 1;
            }
        }
    }
    return 0;
}

int delete(int data) {
    Node *p = head;
    if (head == NULL) {
        return 0;
    } else {
        while (p->next != NULL) {
            if (p->data == data) {
                Node *d = p;
                p->prev->next = p->next;
                p->next->prev = p->prev;
                free(d);
                return 1;
            }
            p = p->next;
        }
    }
    return 0;
}

void print_forward(void) {
    Node *p = head;
    
    while (p != NULL) {
        if (p->next != NULL)
            printf("%d -> ", p->data);
        else
            printf("%d\n", p->data);
        p = p->next;
    }
}

void print_reverse(void) {
    Node *p = head;
    
    while (p->next != NULL)
        p=p->next;
    
    while (p != NULL) {
        if (p->prev != NULL)
            printf("%d -> ", p->data);
        else
            printf("%d\n", p->data);
        p = p->prev;
    }
}

void makeTestFile(void) {
    int i, j;
    FILE *outfile;
    outfile = fopen("test_input.txt", "w");
    
    for(i=0; i<100; i++) {
        j = rand() % 1000;
        fprintf(outfile, "INSERT %d\n", j);
    }
    
    fprintf(outfile, "ASCEND\n");
    fprintf(outfile, "DESCEND\n");
    
    for(i=0; i<100; i++) {
        j = rand() % 1000;
        fprintf(outfile, "DELETE %d\n", j);
    }
    
    fprintf(outfile, "ASCEND\n");
    fprintf(outfile, "DESCEND\n");
    
    fclose(outfile);
    
    
}

void testRun(void) {
    makeTestFile();
    FILE *infile;
    infile = fopen("test_input.txt", "r");
    
    char *buffer = (char *)malloc(sizeof(char) * 20);
    if (infile == NULL) {
        printf("File does not found.\n");
        return;
    }
    while (!feof(infile)) {
        char *ptr, *command[2];
        
        fgets(buffer, 20, infile);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        ptr = strtok(buffer, " ");
        
        for (int i = 0; ptr != NULL;) {
            command[i++] = ptr;
            ptr = strtok(NULL, " ");
        }
        
        if (strcmp(command[0], "INSERT") == 0)
            insert(atoi(command[1]));
        
        else if (strcmp(command[0], "DELETE") == 0)
            delete(atoi(command[1]));
        
        else if (strcmp(command[0], "ASCEND") == 0)
            print_forward();
        
        else if (strcmp(command[0], "DESCEND") == 0)
            print_reverse();
    }
}

void run(char* argv[]) {
    FILE *infile;
    infile = fopen(argv[1], "r");
    
    char *buffer = (char *)malloc(sizeof(char) * 20);
    if (infile == NULL) {
        printf("File does not found.\n");
        return;
    }
    while (!feof(infile)) {
        char *ptr, *command[2];
        
        fgets(buffer, 20, infile);
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        ptr = strtok(buffer, " ");
        
        for (int i = 0; ptr != NULL;) {
            command[i++] = ptr;
            ptr = strtok(NULL, " ");
        }
        
        if (strcmp(command[0], "INSERT") == 0)
            insert(atoi(command[1]));
        
        else if (strcmp(command[0], "DELETE") == 0)
            delete(atoi(command[1]));
        
        else if (strcmp(command[0], "ASCEND") == 0)
            print_forward();
        
        else if (strcmp(command[0], "DESCEND") == 0)
            print_reverse();
    }
}

int main(int argc, char * argv[]) {
//    testRun();
    run(argv);
    return 0;
}
