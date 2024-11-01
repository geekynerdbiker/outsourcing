/********************************************
 Class: Data Structure and Algorithms, KECE208_02
 2nd semester, 2022
 
 1st Project: List
 
 linked_list.c
 
 Name:
 StudentID:
 E-mail:
 
 **********************************************/

#include "linked_list.h"
#include "string.h"
int list_exist;

/*
 @Function name:
 @Parameters:
 @Returns:
 @Descriptions:
 @Error cases:
 */

struct linked_list* create_list (int number_of_nodes, int list_type)
{
    int a[number_of_nodes];
    int i, j;
    int bFound;
    
    if (number_of_nodes < 1)
    {
        printf("Function create_list: the number of nodes is not specified correctly\n");
        return NULL;
    }
    if(list_exist == 1)
    {
        printf("Function create_list: a list already exists\nRestart a Program\n");
        exit(0);
    }
    if(list_type != 0 && list_type != 1)
    {
        printf("Function create_list: the list type is wrong\n");
        exit(0);
    }
    struct linked_list * new_list = (struct linked_list*)malloc(sizeof(struct linked_list));
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->number_of_nodes = 0;
    new_list->type_of_list = list_type;
    
    //now put nodes into the list with random numbers.
    srand((unsigned int)time(NULL));
    if(list_type == 0)
    {
        for ( i = 0; i < number_of_nodes; ++i )
        {
            while ( 1 )
            {
                
                a[i] = rand() % number_of_nodes + 1;
                bFound = 0;
                for ( j = 0; j < i; ++j )
                {
                    if ( a[j] == a[i] )
                    {
                        bFound = 1;
                        break;
                    }
                }
                if ( !bFound )
                    break;
            }
            struct linked_node* new_node = create_node(a[i]);
            insert_node(new_list, new_node);
        }
    }
    else if(list_type == 1)
    {
        for ( i = 0; i < number_of_nodes; ++i )
        {
            while ( 1 )
            {
                
                a[i] = rand() % number_of_nodes + 1;
                bFound = 0;
                for ( j = 0; j < i; ++j )
                {
                    if ( a[j] == a[i] )
                    {
                        bFound = 1;
                        break;
                    }
                }
                if ( !bFound )
                    break;
            }
            struct linked_node* new_node = create_node(a[i]);
            push_Stack(new_list, new_node);
        }
    }
    list_exist = 1;
    printf("List is created!\n");
    return new_list;
}

/*
 @Function name:
 @Parameters:
 @Returns:
 @Descriptions:
 @Error cases:
 */

void remove_list(struct linked_list* list)
{
    //your code starts from here
    int nodes = list->number_of_nodes;
    
    if (nodes == 1) {
        struct linked_node* del = list->head;
        printf("The node with value %d is deleted!\n", del->value);
        free(del);
        list->number_of_nodes--;
        free(list);
        list_exist = 0;
        printf("The list is completely deleted: %d nodes are deleted\n", nodes);
    } else {
        struct linked_node* del = list->head;
        list->head = del->next;
        
        printf("The node with value %d is deleted!\n", del->value);
        free(del);
        
        while (list->head != NULL) {
            struct linked_node* realDelNode = list->head;
            list->head = list->head->next;
            printf("The node with value %d is deleted!\n", realDelNode->value);
            free(realDelNode);
            list->number_of_nodes--;
        }
        
        free(list);
        list_exist = 0;
        printf("The list is completely deleted: %d nodes are deleted\n", nodes);
    }
}

/*
 @Function name:
 @Parameters:
 @Returns:
 @Descriptions:
 @Error cases:
 */

struct linked_node* create_node (int node_value)
{
    struct linked_node* node = (struct linked_node*)malloc(sizeof(struct linked_node));
    node->value = node_value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

/*
 @Function name:
 @Parameters:
 @Returns:
 @Descriptions:
 @Error cases:
 */

void insert_node(struct linked_list* list, struct linked_node* node)
{
    node->next = NULL;
    node->prev = NULL;
    
    if(list->head == NULL) {
        list->head = node;
        list->tail = node;
        list_exist = 1;
    } else if(list->head == list->tail) {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    } else if(list->head != list->tail) {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    
    (list->number_of_nodes)++;
    list->type_of_list = 0;
}


/*
 @Function name:
 @Parameters:
 @Returns:
 @Descriptions:
 @Error cases:
 */

void remove_node(struct linked_list* list, int rm_node_value)
{
    //your code starts from here
    if (list_exist == 0) {
        printf("There is no list.\n");
        exit(0);
    } if (list->type_of_list == 1) {
        printf("Function remove_node: The list type is not normal. Removal is not allowed\n");
        exit(0);
    }
    
    struct linked_node* cur = list->head;
    struct linked_node* del = list->head;
    
    while (1) {
        if (cur->value == rm_node_value) {
            del = cur;
            break;
        } if (cur->next == NULL)
            break;
        
        cur = cur->next;
    }
    
    if (del->value != rm_node_value) {
        printf("Function remove_node: There is no such node to remove\n");
        exit(0);
    } if (list->number_of_nodes == 1) {
        free(del);
        list->number_of_nodes--;
        printf("node deleted\n");
        free(list);
        list_exist = 0;
        printf("list deleted\n");
    } else if (del == list->head) {
        list->head = del->next;
        list->head->prev = NULL;
        free(del);
        list->number_of_nodes--;
        printf("node deleted\n");
    } else if(del == list->tail) {
        list->tail = del->prev;
        list->tail->next = NULL;
        free(del);
        list->number_of_nodes--;
        printf("node deleted\n");
    } else {
        del->prev->next = del->next;
        del->next->prev = del->prev;
        
        free(del);
        list->number_of_nodes--;
        
        printf("node deleted\n");
    }
    
    return;
}

/*
 @Function name:
 @Parameters:
 @Returns:
 @Descriptions:
 @Error cases:
 */
void delete_range(struct linked_list* list, int id_1, int id_2)
{
    //your code starts from here
    if (id_1 > id_2) {
        printf("Function delete_range: the selected range of nodes is not in order\n");
        exit(0);
    }
    if (list->number_of_nodes < id_1 || list->number_of_nodes < id_2 || id_1 < 0 || id_2 < 0) {
        printf("Function delete range: the node does not exist\n");
        exit(0);
    }
    
    struct linked_node* cur = list->head;
    
    for (int i = 0; i < id_1-1; i++)
        cur = cur->next;
    for (int i = id_1; i <= id_2; i++) {
        struct linked_node* tmp = cur;
        cur = cur->next;
        remove_node(list, tmp->value);
    }
}

/*
 @Function name:
 @Parameters:
 @Returns:
 @Descriptions:
 @Error cases:
 */
void push_Stack(struct linked_list* list, struct linked_node* node)
{
    //your code starts from here
    if (list->type_of_list == 0) {
        printf("Function push_Stack: The list type is not a stack\n");
        exit(0);
    }
    
    struct linked_node* newNode = node;

    if (list->number_of_nodes == 0) {
        list->head = newNode;
        list->tail = newNode;
        list->number_of_nodes++;
        return;
    } else {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
        list->number_of_nodes++;
        return;
    }
}

/*
 @Function name:
 @Parameters:
 @Returns:
 @Descriptions:
 @Error cases:
 */
void pop_Stack(struct linked_list* list, int number)
{
    //your code starts from here
    if (list->type_of_list == 0) {
        printf("Function push_Stack: The list type is not a stack\n");
        exit(0);
    }
    
    if (list->number_of_nodes < number) {
        printf("Function popStack: The number of nodes which will be removed is more than that in the stack\n");
        exit(0);
    } else if (number < 1) {
        printf("Function popStack: The number of nodes which will be removed is more than 1\n");
        exit(0);
    } else if (list->number_of_nodes == number) {
        while(1) {
            struct linked_node* del = list->tail;
            list->tail = del->prev;
            list->tail->next = NULL;
            free(del);
            list->number_of_nodes--;
            number--;
            if(number == 1)
                break;
        }
        
        struct linked_node* del = list->head;
        free(del);
        list->number_of_nodes--;
        free(list);
        list_exist = 0;
        return;
        
    } else {
        while(1) {
            struct linked_node* del = list->tail;
            list->tail = del->prev;
            list->tail->next = NULL;
            free(del);
            list->number_of_nodes--;
            number--;
            if(number == 0)
                break;
        }
        
        return;
    }
}

/*
 @Function name:
 @Parameters:
 @Returns:
 @Descriptions:
 @Error cases:
 */

void search_node(struct linked_list* list, int find_node_value)
{
    //your code starts from here
    if (list->head == NULL) {
        printf("Function search_node : There is no such node to search.");
        exit(0);
    }
    
    struct linked_node* cur = list->head;
    int od = 1;
    
    if (cur->value == find_node_value) {
        printf("The order of %d is %d.\n", find_node_value, od);
        return;
    } while(cur->next != NULL) {
        cur = cur->next;
        od++;
        
        if (cur->value == find_node_value) {
            printf("The order of %d is %d.\n", find_node_value, od);
            return;
        }
    }
    
    printf("Function search_node : There is no such node to search.\n");
    exit(0);
}

/*
 @Function name:
 @Parameters:
 @Returns:
 @Descriptions:
 @Error cases:
 */
void swap_nodes(struct linked_list* list, int node1, int node2)
{
    //your code starts from here
    if (list->number_of_nodes < 2) {
        printf("Function swap_nodes: The list size is smaller than 2, there is nothing to swap\n");
        exit(0);
    } if (node1 == node2) {
        printf("Function swap_nodes: The node numbers are the same. Nothing to swap\n");
        exit(0);
    }
    
    struct linked_node* n1 = list->head;
    struct linked_node* n2 = list->head;
    
    while (n1 != NULL) {
        if (n1->value == node1)
            break;
        n1 = n1->next;
    } while (n2 != NULL) {
        if (n2->value == node2)
            break;
        n2 = n2->next;
    }
    
    if (n1 == NULL || n2 == NULL) {
        printf("Function swap_nodes: either one of the nodes is not available\n");
        exit(0);
    }
    
    n1->prev->next = n2;
    n1->next->prev = n2;
    n2->prev->next = n1;
    n2->next->prev = n1;
    
}

/*
 @Function name:
 @Parameters:
 @Returns:
 @Descriptions:
 @Error case:
 */
void forward_by_one(struct linked_list* list)
{
    //your code starts from here
    if (list->number_of_nodes < 2) {
        printf("Function forward_by_one: The list size is smaller than 2, there is nothing to rotate\n");
        exit(0);
    } if (list->type_of_list != 0) {
        printf("Function forward_by_one: The list type is not normal\n");
        exit(0);
    }
    
    struct linked_node* h = list->head;
    struct linked_node* t = list->tail;

    list->head = h->next;
    h->next->prev = h->prev;
    h->next = t->next;
    h->prev = t;
    t->next = h;
    list->tail = h;
}

/*
 @Function name:
 @Parameters:
 @Returns:
 @Descriptions:
 @Error cases:
 */
void backward_by_one(struct linked_list* list)
{
    //your code starts from here
    if (list->number_of_nodes < 2) {
        printf("Function backward_by_one: The list size is smaller than 2, there is nothing to rotate\n");
        exit(0);
    } if (list->type_of_list != 0) {
        printf("Function backward_by_one: The list type is not normal\n");
        exit(0);
    }
    
    struct linked_node* h = list->head;
    struct linked_node* t = list->tail;

    list->tail = t->prev;
    t->next = h;
    t->prev = h->prev;
    h->prev = t;
    list->head = t;
    
    
}

/*
 @Function name:
 @Parameters:
 @Returns:
 @Descriptions:
 @Error cases:
 */

void reverse_range(struct linked_list* list, int order1, int order2)
{
    //your code starts from here
    if(order1 > order2 || order1 <= 0 || order2 > list->number_of_nodes) {
        printf("Function reverse_range: Input value is invalid");
        exit(0);
    }
    
    if (order1 == order2) return;
    
    int n = order1-order2+1;
    int order = 1;
    struct linked_node* stg[order2-order1+1];
    struct linked_node* cur = list->head;
    
    if (order1 == 1 && order2 == list->number_of_nodes) {
        reverse_range(list, order1+1, order2-1);
        list->tail->prev->next = list->head;
        list->head->prev = list->tail->prev;
        list->head->next->prev = list->tail;
        list->tail->next = list->head->next;
        
        list->head = list->tail;
        list->tail = cur;
        list->head->prev = NULL;
        list->tail->next = NULL;
        
        return;
        
    } else if(order1 == 1) {
        struct linked_node* postNode = list->tail;
        while(1) {
            if(order == order2+1) postNode = cur;
            if(order >= order1 && order <= order2) stg[order-order1] = cur;
            if(cur->next == NULL) break;
            
            order++;
            cur = cur->next;
        }
        order = order2-order1;
        list->head = stg[order];
        list->head->prev = NULL;
        postNode->prev=stg[0];
        stg[0]->next = postNode;
        
        for (int i = order; i > 0; i--) {
            stg[i]->next = stg[i-1];
            stg[i-1]->prev = stg[i];
        }

        return;
        
        
    } else if (order2 == list->number_of_nodes) {
        struct linked_node* preNode = list->head;
        while(1) {
            if (order == order1-1) preNode = cur;
            if (order >= order1 && order <= order2) stg[order-order1] = cur;
            if (cur->next == NULL) break;
            order++;
            cur = cur->next;
        }
        
        order = order2-order1;
        list->tail = stg[0];
        list->tail->next = NULL;
        preNode->next = stg[order];
        stg[order]->prev = preNode;
        
        for (int i =  order; i > 0; i--) {
            stg[i]->next = stg[i-1];
            stg[i-1]->prev = stg[i];
        }
        
        return;
        
    } else {
        struct linked_node* preNode = list->head;
        struct linked_node* postNode = list->tail;
        while(1) {
            if (order == order1-1) preNode = cur;
            if (order == order2+1) postNode = cur;
            if (order >= order1 && order <= order2) stg[order-order1] = cur;
            if (cur->next == NULL) break;
            order++;
            cur = cur->next;
        }
        
        preNode->next = postNode;
        postNode->prev = preNode;
        cur = preNode;
        order = order2-order1;
        
        while(1) {
            cur->next = stg[order];
            stg[order]->prev = cur;
            stg[order]->next = (order==0) ? postNode : stg[--order];
            if(stg[order]->next == postNode) {
                postNode->prev = stg[order];
                break;
            }
            cur = cur->next;
        }
        
        return;
        
    }
}

/*
 @Function name:
 @Parameters:
 @Returns:
 @Descriptions:
 @Error cases:
 */

void powerofN_reverse(struct linked_list* list, int n)
{
    //your code starts from here
    int sum = 0;
    
    for (int i = 0; sum < list->number_of_nodes; i++) {
        int len = (int)pow(n, i);
        sum += len;
        if (sum < list->number_of_nodes)
            reverse_range(list, len, (int)pow(n, i+1)-1);
        else
            reverse_range(list, len, list->number_of_nodes);
    }
}

/*
 @Function name:
 @Parameters:
 @Returns:
 @Descriptions:
 @Error cases:
 */
void print_list(struct linked_list* list)
{
    if(list_exist == 0)
    {
        printf("There is no list to print\n");
        return;
    }
    struct linked_node * temp = list->head;
    printf("****************************************************************************\n\n");
    printf("	Number of nodes: %d\n", list->number_of_nodes);
    printf("\n");
    int i=0;
    for(i=0; i < list->number_of_nodes; i++)
    {
        printf ("%d   ", temp->value);
        temp = temp->next;
    }
    printf("\n");
    printf("****************************************************************************\n\n");
    free(temp);
}

