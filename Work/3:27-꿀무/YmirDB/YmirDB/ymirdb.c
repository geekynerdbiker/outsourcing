/**
 * comp2017 - assignment 2
 * <your name>
 * <your unikey>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <ctype.h>
#include "ymirdb.h"

struct entry *head1 = NULL;
struct element *head2 = NULL;

//
// We recommend that you design your program to be
// modular where each function performs a small task
//
// e.g.
//
// command_bye
// command_help
// ...
// entry_add
// entry_delete
// ...
//


void command_bye() {
    printf("bye\n");
}

void command_help() {
    printf("%s\n", HELP);
}

void print_keys(entry *n){
    while(n != NULL){
        printf("%s\n", n->key);
        n = n->next;
    }
}

void print_values(element *n){
    while(n != NULL){
        if(n->type == 0){
            printf("%d ", n->value);
            n = n->next;
        }
        else if (n->type == 1){
            printf("%s ", head2->entry->key);
            n = n->next;
        }
        
    }
}
bool key_exists_check(char *key_to_check){
    return true;
}

int command_set(char * set_command){
    bool is_key_valid = false;
    int result;
    bool key_exists = false;
    char * KEY = strsep(&set_command, " ");
    
    if (((((int)KEY[0] >=  97 && (int) KEY[0] <= 122) || (int)KEY[0] >= 65 && (int)KEY[0] <= 90)) && strlen(KEY) <= 15){
        is_key_valid = true;
    } else return -1;
    
    struct entry * new_node;
    struct entry * to_check_if_key_exists = head1;
    while(to_check_if_key_exists != NULL){
        if (strcmp(to_check_if_key_exists->key, KEY) == 0){
            new_node = to_check_if_key_exists;
            key_exists = true;
            break;
        }else{
            to_check_if_key_exists = to_check_if_key_exists->next;
        }
    }

    if(!key_exists){
        new_node = (struct entry *) malloc(sizeof(struct entry));
    }
    
    strcpy(new_node->key, KEY);
    
    char *lineptr = set_command;
    char *values = strsep(&lineptr, " ");
    char values_arr[MAX_LINE] = " ";
    char temp_key[MAX_KEY] = "\0";
    int key_compare;

    while (values != NULL){
        if (((int) values[0] >=  97 && (int) values[0] <= 122) || (int)values[0] <= 41 && (int)values[0] <= 132){
            strcat(temp_key, values);
            strcat(values_arr, values);

        }
        else{
            strcat(values_arr, values);
            strcat(values_arr, " ");
        }
        values = strsep(&lineptr, " ");
    }
    temp_key[strcspn(temp_key, "\n")] = 0;
    
    key_compare = strcmp(KEY, temp_key);
    if(key_compare == 0){
        printf("not permitted\n");
        return -1;
    }

    for(int i = 0; i < strlen(values_arr); i++){
        if(values_arr[i] != ' ' && values_arr[i] != '\n'){
            int temp_val = abs(values_arr[i]);
            if (temp_val - 48 >= 0 && temp_val - 48 <= 9){
                struct element * new_element = (struct element *) malloc(sizeof(struct element));
                new_element->type = 0;
                new_element->value = (int)values_arr[i] - 48;
                new_element->next = NULL;
                
                if(head2 == NULL){
                    head2 = new_element;
                }else {
                    struct element * temp_head2 = head2;
                    while(temp_head2->next != NULL){
                        temp_head2 = temp_head2->next;
                    }
                    temp_head2->next = new_element;
                }
            }

            else {
                struct entry *temp_entry = head1;
                while(temp_entry != NULL){
                    if(strcmp(temp_entry->key, temp_key) != 0){
                        temp_entry = temp_entry->next;
                    }else{
                        break;
                    }
                }
                if (temp_entry != NULL){
                    struct element * new_element2 = (struct element *) malloc(sizeof(struct entry));
                    new_element2->type = 1;
                    new_element2->entry = temp_entry;
                    new_element2->next = NULL;

                    if(head2 == NULL){
                        head2 = new_element2;
                    }else {
                        struct element * temp_head2 = head2;
                        while(temp_head2->next != NULL){
                            temp_head2 = temp_head2->next;
                        }
                        temp_head2->next = new_element2;
                    }
                }else{
                    printf("key doesn't exist\n");
                    return -1;
                }
            }
        }
    }

    if (head1 == NULL){
        head1 = new_node;
        new_node->next = NULL;
        new_node->values = head2;
        new_node->prev = NULL;
    } else{
        struct entry *temp = head1;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new_node;
        new_node-> next = NULL;
        new_node->values = head2;
        new_node->prev = temp;
    }
    
    head2 = NULL;
    printf("ok\n");

    return 0;
}


void command_push_append(char * push_append_full_command){
    char * push_append_command = strsep(&push_append_full_command, " ");
    char *key = strsep(&push_append_full_command, " ");
    char *pushptr = push_append_full_command;
    char push_val_arr[MAX_LINE] = "";
    pushptr = strsep(&push_append_full_command, " ");

    int choice = 0;
    if (strcasecmp(push_append_command, "PUSH")){
        choice = 1;
    }else{
        choice = 2;
    }

    while (pushptr != NULL){
        strcat(push_val_arr, pushptr);
        strcat(push_val_arr, " ");
        pushptr = strsep(&push_append_full_command, " ");
    }
     printf("%s\n", push_val_arr);
}


void command_get(char * get_full_command){
    struct entry *get_node = head1;
    struct element *get_values = head2;
    
    get_full_command[strcspn(get_full_command, "\n")] = 0;

    if(get_node == NULL){
        printf("no such key\n");
    }else{
        while((strcmp(get_node->key, get_full_command)) != 0 && get_node != NULL){
            get_node = get_node->next;
        }
        if(get_node != NULL){
            get_values = get_node->values;
            if (get_values == NULL){
            }
            printf("[ ");
            while(get_values != NULL){
                if (get_values->type == 0){
                    printf("%d ", get_values->value);
                    get_values = get_values->next;
                }
                else{
                    printf("%s ", get_values->entry->key);
                    get_values = get_values->next;
                }
            }
            printf("]\n");
        }
    }
}

int main(void) {

    char line[MAX_LINE];
    char *linecp;
    char *command;

    while (true) {
        printf("> ");

        if (NULL == fgets(line, MAX_LINE, stdin)) {
            linecp = strdup(line);
            printf("\n");
            command_bye();
            return 0;
        } else {
            linecp = strdup(line);
            command = strsep(&linecp, " ");
            command[strcspn(command, "\n")] = 0;
            int result;

            if((result = strcasecmp(command, "SET")) == 0){
                char set_command[MAX_LINE] = "";
                command = strsep(&linecp, " ");
                while (command != NULL){
                    strcat(set_command, command);
                    strcat(set_command, " ");
                    command = strsep(&linecp, " ");
                }
                command_set(set_command);

            }
            else if ((result = strcasecmp(command, "GET")) == 0){
                char *node_to_print = strsep(&linecp, " ");
                command_get(node_to_print);
                
            }
            else if ((result = strcasecmp(command, "SUM")) == 0){
                
            }
            else if ((result = strcasecmp(command, "LIST ENTRIES")) == 0){
                
            }
            else if ((result = strcasecmp(command, "LIST KEY")) == 0){
                
            }
            else if ((result = strcasecmp(command, "LIST SNAPSHOTS")) == 0){
                
            }
            else if ((result = strcasecmp(command, "FORWARD")) == 0){
                
            }
            else if ((result = strcasecmp(command, "BACKWARD")) == 0){
                
            }
            else if ((result = strcasecmp(command, "DEL")) == 0){
                
            }
            else if ((result = strcasecmp(command, "PURGE")) == 0){
                
            }
            else if ((result = strcasecmp(command, "SNAPSHOT")) == 0){
                
            }
            else if ((result = strcasecmp(command, "PLUCK")) == 0){
                
            }
            else if ((result = strcasecmp(command, "POP")) == 0){
                
            }
            else if ((result = strcasecmp(command, "APPEND")) == 0){
                printf("command is append\n");
                char append_command[MAX_LINE] = "";
                // command = strsep(&linecp, " ");
                while(command != NULL){
                    command[strcspn(command,"\n")] = 0;
                    strcat(append_command, command);
                    strcat(append_command, " ");
                    command = strsep(&linecp, " ");
                }
                command_push_append(append_command);
            }
            else if ((result = strcasecmp(command, "PICK")) == 0){
                
            }
            else if ((result = strcasecmp(command, "PUSH")) == 0){
                char push_command[MAX_LINE] = "";
                while(command != NULL){
                    command[strcspn(command,"\n")] = 0;
                    strcat(push_command, command);
                    strcat(push_command, " ");
                    command = strsep(&linecp, " ");
                }
                command_push_append(push_command);
                
                
            }
            else if ((result = strcasecmp(command, "DROP")) == 0){
                
            }
            else if ((result = strcasecmp(command, "ROLLBACK")) == 0){
                
            }
            else if ((result = strcasecmp(command, "CHECKOUT")) == 0){
                
            }
            else if ((result = strcasecmp(command, "MIN")) == 0){
                
            }
            else if ((result = strcasecmp(command, "MAX")) == 0){
                
            }
            else if ((result = strcasecmp(command, "LEN")) == 0){
                
            }
            else if ((result = strcasecmp(command, "REV")) == 0){
                
            }
            else if ((result = strcasecmp(command, "UNIQ")) == 0){
                
            }
            else if ((result = strcasecmp(command, "SORT")) == 0){
                
            }
            else if ((result = strcasecmp(command, "TYPE")) == 0){
                
            }
            else if ((result = strcasecmp(command, "BYE")) == 0){
                command_bye();
                break;
            }
        }
      }

    return 0;
}
