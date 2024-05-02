#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TABLE_SIZE_1 11
#define TABLE_SIZE_2 8
#define TABLE_SIZE_3 7

typedef struct Node {
    int key;
    struct Node *next;
} Node;

Node *create_node(int key) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->key = key;
    node->next = NULL;
    return node;
}

void insert(Node **table, int key, int table_size) {
    int index = key % table_size;
    Node *node = create_node(key);
    if (table[index] == NULL) {
        table[index] = node;
    } else {
        Node *curr = table[index];
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = node;
    }
}

void print_table(Node **table, int table_size) {
    int max_chain_length = 0;
    int total_chain_length = 0;
    for (int i = 0; i < table_size; i++) {
        printf("Chain %d: ", i);
        int chain_length = 0;
        Node *curr = table[i];
        
        while (curr != NULL) {
            printf("%d -> ", curr->key);
            curr = curr->next;
            chain_length++;
        }
        
        if (chain_length > max_chain_length) {
            max_chain_length = chain_length;
        }
        total_chain_length += chain_length;
        printf("NULL\n");
    }
    double avg_chain_length = (double) total_chain_length / table_size;
    
    printf("Longest chain length: %d\n", max_chain_length);
    printf("Average chain length: %f\n", avg_chain_length);
}

void insert_keys(Node **table, int table_size, int num_keys) {
    srand(time(NULL));
    for (int i = 0; i < num_keys; i++) {
        int key = rand() % 1000;
        insert(table, key, table_size);
    }
}

int main() {
    Node *table1[TABLE_SIZE_1] = { NULL };
    Node *table2[TABLE_SIZE_2] = { NULL };
    Node *table3[TABLE_SIZE_3] = { NULL };
    
    int num_keys = 60;
    
    insert_keys(table1, TABLE_SIZE_1, num_keys);
    insert_keys(table2, TABLE_SIZE_2, num_keys);
    insert_keys(table3, TABLE_SIZE_3, num_keys);
    
    printf("Table 1:\n");
    print_table(table1, TABLE_SIZE_1);
    printf("\nTable 2:\n");
    print_table(table2, TABLE_SIZE_2);
    printf("\nTable 3:\n");
    print_table(table3, TABLE_SIZE_3);
    
    return 0;
}
