#include "PriorityQueue.hpp"


// Part 1: Basic operations of priority queue (40 pts)
PriorityQueue::PriorityQueue(int direction) {   // Constructor.
    // TO-DO
    this->direction = direction;
    this->root_index = 0;
}


PriorityQueue::~PriorityQueue() {   // Destructor.
    // TO-DO
}


void PriorityQueue::swapPQ(int idx1, int idx2) {    // Swaps the elements at the specified indices in the heap.
    // TO-DO
    std::swap(this->heap[idx1], this->heap[idx2]);
}


void PriorityQueue::upHeap(int idx) {   // Adjust the heap by moving the specified element upwards.
    // TO-DO
    int parentIdx = idx / 2;
    
    while (idx > this->root_index && ((this->direction == 1 && this->heap[parentIdx] < this->heap[idx]) || (this->direction == -1 && this->heap[parentIdx] > this->heap[idx]))) {
        swapPQ(parentIdx, idx);
        idx = parentIdx;
        parentIdx = idx / 2;
    }
}


void PriorityQueue::downHeap(int idx) { // Adjust the heap by moving the specified element downwards.
    // TO-DO
    int left_idx = 2 * idx + 1;
    int right_idx = 2 * idx + 2;
    int child_idx = idx;
    
    while (true) {
        if (left_idx < this->heap.size() &&
            ((this->direction == 1 && this->heap[left_idx] > this->heap[idx]) || (this->direction == -1 && this->heap[left_idx] < this->heap[idx]))) {
            child_idx = left_idx;
        }
        
        if (right_idx < this->heap.size() &&
            ((this->direction == 1 && this->heap[right_idx] > this->heap[child_idx]) || (this->direction == -1 && this->heap[right_idx] < this->heap[child_idx]))) {
            child_idx = right_idx;
        }
        
        if (child_idx != idx) {
            swapPQ(idx, child_idx);
            idx = child_idx;
            left_idx = 2 * idx + 1;
            right_idx = 2 * idx + 2;
        } else {
            break;
        }
    }
}


void PriorityQueue::insertHeap(int e) { // Insert a new entry to the queue.
    // TO-DO
    this->heap.push_back(e);
    upHeap(this->heap_size - 1);
}


int PriorityQueue::popHeap() {  // Pop its top entry. If the queue is empty, then print "Empty queue.".
    // TO-DO
    if (this->heap.size() == 0) {
        return -1;
    }
    
    int top = this->heap[0];
    this->heap.erase(this->heap.begin());
    downHeap(this->root_index);
    
    return top;
}


int PriorityQueue::topHeap() const {    // Return its top entry. If the queue is empty, then print "Empty queue.".
    // TO-DO
    if (this->heap.size() == 0) {
        return -1;
    }
    
    return this->heap[this->root_index];
}


int PriorityQueue::sizeHeap() const {   // Return size of queue.
    // TO-DO
    return (int)this->heap.size();
}


bool PriorityQueue::emptyHeap() const { // Check if the queue is empty. `1` for empty queue.
    // TO-DO
    return (int)this->heap.size() == 0;
}



// Part 2: Document printer implementation with priority queue (60 pts)
Document::Document(std::string id, std::string title, int priority) {   // Constructor.
    // TO-DO
    this->id = id;
    this->title = title;
    this->priority = priority;
}


std::string Document::getId() const {   // Getter.
    // TO-DO
    return this->id;
}


std::string Document::getTitle() const {    // Getter.
    // TO-DO
    return this->title;
}


int Document::getPriority() const { // Getter.
    // TO-DO
    return this->priority;
}


Printer::Printer() {    // Constructor.
    // TO-DO
    this->heap_size = 0;
    this->root_index = 0;
}


Printer::~Printer() {   // Destructor.
    // TO-DO
}


void Printer::swapDoc(int idx1, int idx2) { // Swaps the elements at the specified indices in the printer.
    // TO-DO
    std::swap(this->docs[idx1], this->docs[idx2]);
}


void Printer::upHeap(int idx) { // Adjust the heap by moving the specified element upwards.
    // TO-DO
    int parent_idx = idx / 2;
    
    while (idx > this->root_index && this->docs[parent_idx].getPriority() > this->docs[idx].getPriority()) {
        swapDoc(idx, parent_idx);
        idx = parent_idx;
        parent_idx = idx / 2;
    }
}


void Printer::downHeap(int idx) {   // Adjust the heap by moving the specified element downwards.
    // TO-DO
    int left_idx = 2 * idx + 1;
    int right_idx = 2 * idx + 2;
    int child_idx = idx;
    
    while (true) {
        if (left_idx < this->heap_size && this->docs[left_idx].getPriority() < this->docs[idx].getPriority()) {
            child_idx = left_idx;
        }
        
        if (right_idx < this->heap_size && this->docs[right_idx].getPriority() < this->docs[child_idx].getPriority()) {
            child_idx = right_idx;
        }
        
        if (child_idx != idx) {
            swapDoc(idx, child_idx);
            idx = child_idx;
            left_idx = 2 * idx + 1;
            right_idx = 2 * idx + 2;
        } else {
            break;
        }
    }
}


void Printer::insertDoc(std::string id, std::string title, int priority) {  // Insert a new doc. (modifiable)
    // TO-DO
    Document new_doc(id, title, priority);
    this->heap_size++;
    this->docs.push_back(new_doc);
    
    upHeap(this->heap_size - 1);
}



Document Printer::popDoc() {    // Pop its top doc. (modifiable)
    // TO-DO
    if (this->heap_size == 0) {
        return Document("", "", -1);
    }
    
    Document top_doc = this->docs[this->root_index];
    this->docs.erase(this->docs.begin() + this->root_index);
    this->heap_size--;
    
    downHeap(this->root_index);
    return top_doc;
}


Document Printer::topDoc() const {  // Returns the document with the highest priority.
    // TO-DO
    if (this->heap_size == 0) {
        return Document("", "", -1);
    }
    
    return this->docs[this->root_index];
}


int Printer::sizePrinter() const {  // Returns the size of the queue.
    // TO-DO
    return this->heap_size;
}


bool Printer::emptyPrinter() const {    // Check if the queue is empty. `1` for empty queue.
    // TO-DO
    return this->heap_size == 0;
}
