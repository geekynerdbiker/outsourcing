#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>

#define MAX_QUEUE_SIZE 999

/**
 * 큐는 연결리스트로 구현
 * 사용 용도 :
 * 1. 후위수식 저장용
*/

typedef struct Node {
  int element; // 수식의 데이터(피연산자 혹은 연산자)
  int type;    // 데이터의 타입 (0: 피연산자 1: 연산자)
  struct Node *next;
} Node;

typedef struct Queue {
  Node *front, *rear; // 큐의 맨 앞과 맨 뒤
  int size;           // 큐의 크기
} Queue;

Queue initQueue(); // 큐 초기화
void enqueue(Queue *queue, int element, int type);
Node dequeue(Queue *queue);
int isQueueFull(Queue *queue);
int isQueueEmpty(Queue *queue);
void destroyQueue(Queue *queue);


#endif