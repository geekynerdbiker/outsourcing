#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * 큐는 연결리스트로 구현
 * 큐는 후위수식 저장용
*/


// 노드 할당
Node* getNode(int element, int type) {
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->element = element;
  newNode->type = type;
  newNode->next = NULL;

  return newNode;
}

// 큐 초기화
Queue initQueue() {
  Queue newQueue;
  newQueue.front = NULL;
  newQueue.rear = NULL;
  newQueue.size = 0;

  return newQueue;
}

int isQueueFull(Queue *queue) {
  return (queue->size >= MAX_QUEUE_SIZE);
}

int isQueueEmpty(Queue *queue) {
  return (queue->size <= 0);
}


void enqueue(Queue *queue, int element, int type) {
  // 큐가 꽉찼을 시 예외처리
  if (isQueueFull(queue)) {
    printf("Queue is Full");
    return;
  }

  Node *newNode = getNode(element, type);
  if (isQueueEmpty(queue)) { // 큐에 첫번째 원소 삽입 시
    queue->front = newNode;
    queue->rear = newNode;
  } else { // 큐에 이후 원소 삽입 시
    queue->rear->next = newNode;
    queue->rear = newNode;
  }
  queue->size++;
}


Node dequeue(Queue *queue) {
  Node tmp; // 삭제 시 반환할 노드
  Node *put = NULL; // 메모리 해제 위한 노드 포인터

  // tmp 초기화
  tmp.element = 0;
  tmp.next = NULL;
  tmp.type = -1;

  // 큐가 비어있을 시 예외처리
  if (isQueueEmpty(queue)) {
    printf("Queue is Empty");
    return tmp;
  }

  // 가장 앞에 있는 노드(front) 수정
  put = queue->front;
  tmp = *(queue->front);
  queue->front = queue->front->next;
  queue->size--;

  // 삭제할 노드 메모리 해제
  free(put);

  return tmp;
}

// 큐 전체 메모리 해제
void destroyQueue(Queue *queue) {
  Node *curr = queue->rear;
  Node *tmp = NULL;
  while(!curr) {
    tmp = curr;
    curr = curr->next;
    free(tmp);
  }
}