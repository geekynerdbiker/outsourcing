#include "MemberQueue.h"

// constructor
MemberQueue::MemberQueue() {
    this->size = 0;
}

// destroyer
MemberQueue::~MemberQueue() {

}

// empty checker
bool MemberQueue::empty() {
    return this->size == 0;
}

// full stack checker
bool MemberQueue::full() {
    return this->size == MAX_SIZE;
}

// push node
void MemberQueue::push(MemberQueueNode* memberQueueNode) {
    // if queue is full do not push
    if (this->full())
        return;

    // if head is not null
    if (head) {
        this->tail->setNext(memberQueueNode);
        memberQueueNode->setPrev(this->tail);
        this->tail = memberQueueNode;
    } else {
        this->head = memberQueueNode;
        this->tail = memberQueueNode;
    }

    this->size++;
}

// pop node from queue
MemberQueueNode *MemberQueue::pop() {
    if (this->empty())
        exit(1);
    
    // iterate pointer
    MemberQueueNode* memberQueueNode = this->head;

    // more than 2 nodes
    if (this->size > 1) {
        this->head = this->head->getNext();
    } else {
        this->head = NULL;
        this->tail = NULL;
    }
    this->size--;
    
    // return target node
    return memberQueueNode;
}

// get head
MemberQueueNode *MemberQueue::front() {
    return this->head;
}
