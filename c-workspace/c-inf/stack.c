#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h>

struct node { 
	int data; 
	struct node* next; 
}; 

struct node* new_node(int data) 
{ 
	struct node* temp_node = (struct node*)malloc(sizeof(struct node)); 
	temp_node->data = data; 
	temp_node->next = NULL; 
	return temp_node; 
} 

// 스택이 비어있는지 확인
int empty(struct node* head) 
{ 
	if(!head){ 
		return 1;
	}
	return 0; 
} 

// 스택에 노드 삽입
void push(struct node** head, int data) 
{ 
	struct node* temp_node = new_node(data); 
	temp_node->next = *head; 
	*head = temp_node; 
} 

// 스택의 마지막 노드 꺼내기
int pop(struct node** head) 
{ 
	if (empty(*head)){
		return INT_MIN;
	}
	struct node* temp = *head; 
	*head = (*head)->next; 
	int element = temp->data; 
	
	return element; 
} 

// 스택의 첫번째 노드 반환
int top(struct node* head) 
{ 
	if(empty(head)) 
		return INT_MIN; 
	return head->data; 
}

// 스택 출력
void display(struct node* head){

	if(empty(head)){
		return;
	}
	struct node* cursor = NULL;
	cursor = head;

	printf("STACK:");
	while (cursor != NULL) {
		printf(" [%c]", cursor->data);
		cursor = cursor->next;
	}
	printf("\n");
	return;
}
