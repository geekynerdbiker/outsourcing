#pragma once
#include <string>

using namespace std;

class MemberQueueNode {
private:
    MemberQueueNode *next;
    MemberQueueNode *prev;
    string name;
    string date;
    int age;
    char term;

public:
    MemberQueueNode(string name, string date, int age, char term) {
        this->next = NULL;
        this->prev = NULL;
        
        this->name = name;
        this->date = date;
        
        this->age = age;
        this->term = term;
    }
    ~MemberQueueNode() {

    }

    MemberQueueNode *getNext() { return this->next; }
    MemberQueueNode *getPrev() { return this->prev; }
    
    void setNext(MemberQueueNode* newNode) { this->next = newNode; }
    void setPrev(MemberQueueNode* newNode) { this->prev = newNode; }
    
    string getName() { return this->name; }
    string getDate() { return this->date; }
    
    int getAge() { return this->age; }
    char getTerm() { return this->term; }

};
