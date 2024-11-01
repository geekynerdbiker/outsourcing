/********************************************
	Class: Data Structure and Algorithms, KECE208_02
		   2nd semester, 2022

	1st Project: List
	linked_list.h

	Name:
	StudentID:
	E-mail:

**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


struct linked_node{
	int value;
	struct linked_node* next;
	struct linked_node* prev;
};

struct linked_list{
	int type_of_list; // normal = 0, stack = 1
	struct linked_node* head;
	struct linked_node* tail;
	int number_of_nodes;
};

//shows whether the list is exist or not
//int list_exist;

//create or remove a list
struct linked_list* create_list (int number_of_nodes, int list_type);
void remove_list(struct linked_list* list);

//create a new node
struct linked_node* create_node (int node_value);

//remove or insert node at proper place
void insert_node(struct linked_list* list, struct linked_node* node);
void remove_node(struct linked_list* list, int rm_node_value);
void push_Stack(struct linked_list * list, struct linked_node* node);
void pop_Stack(struct linked_list* list, int number);

//apply stack and queue mechanism to the lists
void delete_range(struct linked_list*list, int id_1, int id_2);

//find a specific node
void search_node(struct linked_list* list, int find_node_value);

//swap the two nodes
void swap_nodes(struct linked_list* list, int node1, int node2);

//rotate list in various ways
void forward_by_one(struct linked_list* list);
void backward_by_one(struct linked_list* list);

//arrange some nodes in reverse order
void reverse_range(struct linked_list* list, int order1, int order2);

//Arrange all nodes with Nth power number order
void powerofN_reverse(struct linked_list* list, int n);

//print out the list
void print_list(struct linked_list* list);

//delete whole nodes and list
void remove_list(struct linked_list* list);


