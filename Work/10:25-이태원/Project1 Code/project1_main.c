/********************************************
	Class: Data Structure and Algorithms, KECE208_02
		   2nd semester, 2022

	1st Project: List
	project1_main.c

	Name:
	StudentID:
	E-mail:

**********************************************/

#include "linked_list.h"
#include "string.h"
extern int list_exist;

int main(void)
{
	printf("\n\nWelcome to DSA Project1 program! \n");

	struct linked_list* list = NULL;
	list_exist = 0;
	int trigger;
	while(1)
		{
			printf("\n");
			char ch [100];
			printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
			printf("Select the option to test:\n");
			printf("1.	Create List\n");
			printf("2.	Remove List\n");
			printf("3.	Insert Node at head\n");
			printf("4.	Remove Node\n");
			printf("5.	Delete Range\n");
			printf("6.	Push Node to Stack\n");
			printf("7.	Pop Node from Stack\n");
			printf("8.	Search Node\n");
			printf("9.	Swap Nodes\n");
			printf("10.	Forward by One\n");
			printf("11.	Backward by One\n");
			printf("12.	Reverse Range\n");
			printf("13.	Power of N Reverse\n");
			printf("14.	Print the list\n");
			printf("15.	Exit the program\n");
			printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");

			fgets(ch, 100, stdin);
			trigger = atoi(ch);

			if(trigger == 1)
			{
				char number_of_nodes [100];
				char list_type[100];
				int count;
				int type;
				printf("number of nodes: \n");
				fgets(number_of_nodes, 100, stdin);
				count = atoi(number_of_nodes);
				printf("type of list: \n");
				fgets(list_type, 100, stdin);
				type = atoi(list_type);
				list = create_list(count, type);
			}

			else if(trigger == 2)
			{
				if(list_exist == 1)
				{
					printf("\nWant to remove the list? (y/n)\n");
					fgets(ch, 100, stdin);
					ch[strlen(ch)-1] = 0x00;
					if((!strcmp(ch, "yes")) || (!strcmp(ch, "y")))
						remove_list(list);
				}
				else
					printf("Nothing to remove\n");
			}

			else if(trigger == 3)
			{
				int node_value;
				printf("\nType node value\n");
				fgets(ch, 100, stdin);
				node_value = atoi(ch);
				struct linked_node* node = create_node(node_value);
				insert_node(list, node);
			}

			else if(trigger == 4)
			{
				int value;
				printf("\nType node value you want to delete: \n");
				fgets(ch, 100, stdin);
				value = atoi(ch);
				remove_node(list, value);
			}

			else if(trigger == 5)
			{
				int id_1;
				int id_2;
				printf("Type node ID you want to begin deletion: \n");
				fgets(ch, 100, stdin);
				id_1 = atoi(ch);
				printf("Type node ID you want to end deletion: \n");
				fgets(ch, 100, stdin);
				id_2 = atoi(ch);

				delete_range(list, id_1, id_2);
			}

			else if(trigger == 6)
			{
				int node_value;
				printf("\nType node value\n");
				fgets(ch, 100, stdin);
				node_value = atoi(ch);
				struct linked_node* node = create_node(node_value);
				push_Stack(list, node);
			}

			else if(trigger == 7)
			{
				int number;
				printf("\nType number of nodes you want to delete: \n");
				fgets(ch, 100, stdin);
				number = atoi(ch);
				pop_Stack(list, number);
			}

			else if (trigger == 8)
			{
				int value;
				printf("\nType node value you want to search: \n");
				fgets(ch, 100, stdin);
				value = atoi(ch);
				search_node(list, value);
			}

			else if(trigger == 9)
			{
				int value_1;
				int value_2;
				printf("\nType node value you want to swap\n");
				fgets(ch, 100, stdin);
				value_1 = atoi(ch);
				printf("\nType node value you want to swap\n");
				fgets(ch, 100, stdin);
				value_2 = atoi(ch);
				swap_nodes(list, value_1, value_2);
			}

			else if(trigger == 10)
			{
				forward_by_one(list);
			}

			else if(trigger == 11)
			{
				backward_by_one(list);
			}

			else if(trigger == 12)
			{
				int value_1;
				int value_2;
				printf("\nType node order you want to begin rotation: \n");
				fgets(ch, 100, stdin);
				value_1 = atoi(ch);
				printf("Type node order you want to end rotation: \n");
				fgets(ch, 100, stdin);
				value_2 = atoi(ch);

				reverse_range(list, value_1, value_2);
			}

			else if(trigger == 13)
			{
				int value;
				printf("\nType the base of power for reversal: \n");
				fgets(ch, 100, stdin);
				value = atoi(ch);
				powerofN_reverse(list, value);
			}

			else if(trigger == 14)
			{
				print_list(list);
			}

			else if(trigger == 15)
			{
				printf("\nSee you later!\n\n");
				exit(0);
			}

			else
				printf("\nWrong input, try again\n");
		}
		return 0;

}
