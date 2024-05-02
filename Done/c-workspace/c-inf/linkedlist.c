#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
	char data;
	struct _node *next;
}Node, *pNode;

typedef struct _list {
	int count;
	pNode head;
	pNode tail;
}List, *pList;

// Linked List를 만들기 위한 함수.
pList makeList() {
	pList list = (pList)malloc(sizeof(List));
	list->count = 0;
	list->head = NULL;
	list->tail = NULL;
	return list;
}

// Node를 만드는 함수. Data를 입력 받아서 저장하고, 만든 node를 반환한다.
pNode makeNode(char data) {
	pNode node = (pNode)malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	return node;
}

// 집어 넣을 노드인 N을 List L의 가장 처음, 즉 head에 집어 넣는 함수.
void insertFront(pList L, pNode N) {
	if(L->head == NULL) {
		L->head = N;
		L->tail = N;
		N->next = NULL;
	}
	else {
		N->next = L->head;
		L->head = N;
	}
	(L->count)++;
}

// 해당하는 노드가 맞는지 확인
int isNode(pList L, char data) {
	pNode tmp = L->head;
	while(tmp != NULL) {
		if (tmp->data == data) {
			return 1;
		}
		tmp=tmp->next;
	}
	return 0;
}

// 노드를 검색하여 위치를 반환
int searchNode(pList L, char data) {
	pNode tmp = L->head;
	int count = 1;
	while(tmp != NULL) {
		if(tmp->data == data) {
			return count;
		}
		tmp = tmp->next;
		count++;
	}
    return count;
}

// 리스트의 끝에 노드 삽입
void insertBack(pList L, pNode N) {
	if(L->head == NULL) {
		L->head = N;
		L->tail = N;
		N->next = NULL;
	}
	else {
		N->next = NULL;
		L->tail->next = N;
		L->tail = N;
	}
	(L->count)++;
}

// 리스트 출력
void printList(pList L) {
	pNode tmp = L->head;
	for (size_t i = 1; i < L->count; i++)
	{
		printf("%c", tmp->data);
		tmp = tmp->next;
	}
	printf("%c\n", tmp->data);
}

// 노드를 삭제
void deleteData(pList L, int data) {
	pNode tmp = L->head;
	pNode prev = NULL;
	for (size_t i = 0; i < L->count; i++) {
		if(tmp->data == data) {
			if(tmp == L->head) {
				L->head = tmp->next;
				tmp = prev->next;
			}
			else if(tmp == L->tail) {
				L->tail = NULL;
				prev->next = NULL;
				tmp = prev->next;
			}
			else {
				prev->next = tmp->next;
				tmp = prev->next;
			}
			(L->count)--;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

// 리스트의 첫 노드 삭제
void deleteHead(pList L) {
	if (L->head == NULL) ;
	else if (L->head == L->tail) {
		L->head = NULL;
		L->tail = NULL;
		(L->count)--;
	}
	else {
		L->head = L->head->next;
		(L->count)--;
	}
}

// 리스트의 마지막 노드 삭제
void deleteTail(pList L) {
	if (L->head == NULL) ;
	else if (L->head == L->tail) {
		L->head = NULL;
		L->tail = NULL;
		(L->count)--;
	}
	else {
		pNode temp = L->head;
		while ((temp->next) != (L->tail)) {
			temp = temp->next;
		}
		temp->next = NULL;
		L->tail = temp;
		(L->count)--;
	}
}

// 리스트 내 공백 노드 제거
void removeSpace(pList L) {
	pNode temp = L->head;
	pNode prev;
	while (L->head->data == ' ') {
		deleteHead(L);
	}
	while (L->tail->data == ' ') {
		deleteTail(L);
	}
	while (temp != L->tail) {
		if (temp->data == ' ' && temp->next->data == ' ') {
			prev->next = temp->next;
			(L->count)--;
			temp = prev->next;
		}
		else {
			prev = temp;
			temp = temp->next;
		}
	}	
}

// 첫 노드 또는 마지막 노드가 0이면 삭제
void removeZero(pList L) {
	pNode temp = L->head;
	pNode prev;
	while (L->head->data == '0') {
		deleteHead(L);
	}
	while (L->tail->data == '0') {
		deleteTail(L);
	}
}

// 해당 인덱스에 노드 삽입
void insertMid(pList L, int index, pNode N) {
	pNode temp = L->head;
	for (int i = 1; i<index; i++) {
		temp = temp->next;
	}
	N->next = temp->next;
	temp->next = N;
	(L->count)++;
}

// 두 개의 리스트 비교
int compareList(pList a,pList b) {
	pNode a_temp = a->head;
	pNode b_temp = b->head;
	while(a_temp != NULL) {
		if(a_temp->data - b_temp->data > 0) return 1;
		else if(a_temp->data - b_temp->data < 0) return 0;
		a_temp = a_temp->next;
		b_temp = b_temp->next;
	}
	return 1;
}	

// 메모리 할당 해제
void freeList(pList L) {
	pNode tmp = L->head;
	pNode prev = NULL;
	for (size_t i = 0; i < L->count; i++)
	{
		prev = tmp;			
		tmp = tmp->next;	
		free(prev);			
	}
}
