#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "calc.h"

struct nodeL* new_nodeL(pList L) 
{ 
	struct nodeL* temp_node = (struct nodeL*)malloc(sizeof(struct nodeL)); 
	temp_node->data = L; 
	temp_node->next = NULL; 
	return temp_node; 
} 

// 스택이 비어있는지 확인
int emptyL(struct nodeL* head) 
{ 
	if(!head){ 
		return 1;
	}
	return 0; 
} 

// 스택에 노드 리스트 삽입
void pushL(struct nodeL** head, pList L) 
{ 
	struct nodeL* temp_node = new_nodeL(L); 
	temp_node->next = *head; 
	*head = temp_node; 
} 

// 스택의 마지막 노드 리스트 꺼내기
pList popL(struct nodeL** head) 
{ 
	pList L = makeList();
	insertBack(L,makeNode(' '));
	if (emptyL(*head)){
		return L;
	}
	struct nodeL* temp = *head; 
	*head = (*head)->next; 
	pList element = temp->data; 
	
	return element; 
} 

// 스택의 첫번째 노드 리스트 반환
pList topL(struct nodeL* head) 
{ 
	pList L = makeList();
	insertBack(L, makeNode('#'));
	if(emptyL(head)) 
		return L;
	return head->data; 
}

// 스택 출력
void displayL(struct nodeL* head){

	if(emptyL(head)){
		return;
	}
	struct nodeL* cursor = NULL;
	cursor = head;

	printf("STACK:");
	while (cursor != NULL) {
		printList(cursor->data);
		cursor = cursor->next;
	}
	printf("\n");
	return;
}
