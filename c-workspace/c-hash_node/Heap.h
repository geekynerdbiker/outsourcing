#pragma once
#include <iostream>
#include "Node.h"

class Heap {
private:
	int h_size;
	int capacity;
	
	void heapify(int index);

public:
	Node** node;

	Heap(int size);
	~Heap();
	bool isEmpty() const;
	bool isFull() const;
	Node* getParent(int index) const;
	Node* getLeft(int index) const;
	Node* getRight(int index) const;
	int getSize() const;

	void push(int freq, char data);
	void push(int freq, char data, Heap& minHeap);

	Node* pop();
};