#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

const int max = 10000000; //number of message to be sent
pthread_mutex_t lock;
int length = 0; //number of entries in the linked list
pthread_t tid[2];

struct node* head;
struct node* tail;

struct node
{
	struct node* next;
	int data;
};

// (head, 0) -> (1) -> (2) -> (3, tail)
//count(producer) = 3, count(consumer) = 0
// if consumer goes next: (head, 1) -> (2) -> (3, tail)
// if producer goes next: (head, 0) -> (1) -> (2) -> (3) -> (4, tail)
void *consumer(void *vargp)
{
	int count = 0;
	while(count < max)
	{
	// 3) grab the mutex (to avoid critical region stuff), decrement the length, remove the lowest value from the linked list (head), increment count
	//consume messages (data from 0 to max-1, throw error if data out of order), invoke free on the head
	if(head->data != count) {printf("ERROR! data %d should be %d!\n", head->data, count);}
	}
	return NULL;
}

void *producer(void *vargp)
{
	int count = 0;
	while(count < max)
	{
	// 2) grab the mutex (to avoid critical region stuff), increment the length, put the value of count on the linked list, increment count
	//produce messages (data from 0 to max-1), malloc new tails
	}
	return NULL;
}

int main()
{
	// 1) create the list
	pthread_mutex_init(&lock, NULL);
	pthread_create(&tid[0], NULL, &producer, NULL);
	pthread_create(&tid[1], NULL, &consumer, NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[0], NULL);
	if(head != NULL) {printf("ERROR! List not empty\n");}
	exit(0);
}

/*
Useful commands:
pthread_mutex_init(&lock, NULL)
pthread_create(&tid[0], NULL, &producer, NULL);
pthread_join(&tid[1], NULL);
pthread_mutex_lock(&lock);
pthread_mutex_unlock(&lock);
*/
