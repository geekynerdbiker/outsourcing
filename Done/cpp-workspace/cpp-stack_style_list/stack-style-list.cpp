#include <iostream>

using namespace std;

// definition of list node
typedef struct Node {
    int data;
    Node* next;
} Node;

// head of list as global
Node* head = NULL;

void insert(int data) {
    // construct and allocation
    Node *n = (Node*)malloc(sizeof(Node));
    
    n->data = data;
    n->next = NULL;
    
    // pointer
    Node* p = head;
    
    if (head == NULL)
        head = n;
    else {
        // go to end of list
        while (p->next != NULL) {
            p = p->next;
        }
        // push
        p->next = n;
    }
}

int remove() {
    // pointers
    Node* p = head;
    Node* q = NULL;

    // go to end of list
    while (p->next != NULL) {
        q = p;
        p = p->next;
    }

    // pop
    if (p == head) {
        head = NULL;
        return 0;
    }
    q->next = NULL;
    free(p);
    
    return 0;
}

void display() {
    Node* p = head;
    
    while (p != NULL) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
};

int main(int argc, const char * argv[]) {
    while (1) {
        cout << "(1) insert  (2) delete  (3) display  (4) exit : " << endl;
        
        int command;
        cin >> command;
        
        switch (command) {
            case 1:
                cout << "data : " << endl;
                int k;
                cin >> k;
                insert(k);
                break;
            
            case 2:
                cout << "" << endl;
                remove();
                break;
            
            case 3:
                cout << "" << endl;
                
                display();
                break;
            
            case 4:
                exit(0);

            default:
                break;
        }
    }
    
    return 0;
}
