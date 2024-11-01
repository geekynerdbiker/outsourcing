#pragma once

#include "MemberQueueNode.h"
#define MAX_SIZE 100

class MemberQueue
{
private:
    MemberQueueNode *head;
    MemberQueueNode *tail;
    int size;

public:
	MemberQueue();
	~MemberQueue();

	bool empty();
	bool full();
	void push(MemberQueueNode *);
    
	MemberQueueNode *pop();
	MemberQueueNode *front();
};

