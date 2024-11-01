#include "Heap.h"

Heap::Heap(int size) : h_size(0), capacity(size + 1) {
	node = new Node * [capacity];
	if (!node) {
		std::cout << "Error: not allocation!" << std::endl;
	}
}

Heap::~Heap() {
	delete[] node;
}

bool Heap::isEmpty() const {
	return h_size == 0;
}

bool Heap::isFull() const {
	return h_size == capacity - 1;
}

Node* Heap::getParent(int index) const {
	if (index <= 1 || index > h_size)
		return nullptr;

	return node[index / 2];
}

Node* Heap::getLeft(int index) const {
	int leftChild = 2 * index;
	if (leftChild <= h_size)
		return node[leftChild];

	return nullptr;
}

Node* Heap::getRight(int index) const {
	int rightChild = 2 * index + 1;
	if (rightChild <= h_size)
		return node[rightChild];

	return nullptr;
}

int Heap::getSize() const {
	return h_size;
}

void Heap::push(int freq, char data) {
	if (isFull()) {
		std::cout << "Heap is full. Cannot push more elements" << std::endl;
		return;
	}

	Node* newNode = new Node(freq, data);

	node[++h_size] = newNode;
	int current = h_size;

	while (current > 1) {
		int parent = current / 2;
		if (node[current]->getFreq() < node[parent]->getFreq()) {
			Node* temp = node[current];
			node[current] = node[parent];
			node[parent] = temp;

			current = parent;
		}
		else {
			break;
		}
	}
}

void Heap::push(int freq, char data, Heap& minHeap) {
	minHeap.push(freq, data);
}

Node* Heap::pop() {
	if (isEmpty()) {
		std::cout << "Heap is empty. Cannot pop an element" << std::endl;
		return nullptr;
	}

	Node* minNode = node[1];
	node[1] = node[h_size--];
	heapify(1);

	return minNode;
}

void Heap::heapify(int index) {
	int smallerChild = index;
	int leftChild = 2 * index;
	int rightChild = 2 * index + 1;

	if (leftChild <= h_size && node[leftChild]->getFreq() < node[smallerChild]->getFreq())
		smallerChild = leftChild;

	if (rightChild <= h_size && node[rightChild]->getFreq() < node[smallerChild]->getFreq())
		smallerChild = rightChild;

	if (smallerChild != index) {
		Node* temp = node[index];
		node[index] = node[smallerChild];
		node[smallerChild] = temp;

		heapify(smallerChild);
	}
}