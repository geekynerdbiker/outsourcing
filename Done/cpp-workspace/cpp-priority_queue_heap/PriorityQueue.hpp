#include <vector>
#include <string>


// Part 1: Basic operations of priority queue (40 pts)
enum direction{ MIN=1, MAX=-1 };        // 1 for MinHeap, -1 for MaxHeap

class PriorityQueue {
private:
    std::vector<int> heap;              // Heap to implement priority queue.
    int direction;                      // It determines whether it is minHeap or maxHeap.
    int root_index;
    int heap_size;

    void swapPQ(int idx1, int idx2);    // Swaps the elements at the speified indices in the heap.
    void upHeap(int idx);               // Adjust the heap by moving the specified element upwards.
    void downHeap(int idx);             // Adjust the heap by moving the specified element downwards.

public:
    PriorityQueue(int direction);       // Constructor
    ~PriorityQueue();                   // Destructor

    void insertHeap(int e);             // Insert a new entry with priority `e` to the queue.
    int popHeap();                      // Pop its top entry.
    int topHeap() const;                // Return its top entry.
    int sizeHeap() const;               // Return size of queue.
    bool emptyHeap() const;             // Check if the queue is empty. `1` for empty queue.
};


// Part 2: Document printer implementation with priority queue (60 pts)
class Document {
private:
    std::string id;                     // ID of the document. (length <= 10.)
    std::string title;                  // The title of the document.
    int priority;                       // The priority of the document.

public:
    Document(std::string id, std::string title, int priority);      // Constructor

    // Getter functions to access private members.
    std::string getId() const;
    std::string getTitle() const;
    int getPriority() const;
};


class Printer {
private:
    std::vector<Document> docs;         // Queue to implement document printer.
    int heap_size;
    int root_index;

    void swapDoc(int idx1, int idx2);   // Swaps the elements at the specified indices in the printer.
    void upHeap(int idx);               // Adjust the heap by moving the specified element upwards.
    void downHeap(int idx);             // Adjust the heap by moving the specified element downwards.

public:
    Printer();                          // Constructor.
    ~Printer();                         // Destructor.

    // You can modify `insertDoc`, `popDoc` functions.
    // E.g., return type, arguments.
    void insertDoc(std::string id, std::string title, int priority);    // Insert a new document.
    Document popDoc();                      // Pop its top document. (modifiable)
    Document topDoc() const;            // Return the document with the highest priority.
    int sizePrinter() const;            // Return size of queue.
    bool emptyPrinter() const;          // Check if the queue is empty. `1` for empty queue.    
};
