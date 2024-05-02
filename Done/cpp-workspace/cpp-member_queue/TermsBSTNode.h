#pragma once
#include <string>

using namespace std;

class TermsBSTNode {
private:
    TermsBSTNode* parent;
    TermsBSTNode* left;
    TermsBSTNode* right;
    
    string name;
    string date;
    string termDate;
    
    int age;
    int key;

public:
    TermsBSTNode(string name, string date, int age) {
        this->parent = NULL;
        this->left = NULL;
        this->right = NULL;
        
        this->name = name;
        this->date = date;
        this->termDate = "";
        
        this->age = age;
        this->key = 0;
    }
    ~TermsBSTNode() {}

    TermsBSTNode* getParent() { return this->parent; }
    TermsBSTNode* getLeft()    { return left; }
    TermsBSTNode* getRight() { return right; }
    
    void setParent(TermsBSTNode* parent) { this->parent = parent; }
    void setLeft(TermsBSTNode* left) { this->left = left; }
    void setRight(TermsBSTNode* right)    { this->right = right; }
    
    string getName() { return this->name; }
    string getDate() { return this->date; }
    string getTermDate() { return this->termDate; }
    
    int getAge() { return this->age; }
    int getKey() { return this->key; }

    void setTermDate(char term) {
        size_t yearPos = this->date.find_first_of("-");
        size_t monthPos = this->date.find_last_of("-");

        int year = stoi(this->date.substr(0, yearPos));
        int month = stoi(date.substr(yearPos + 1, monthPos - yearPos - 1));
        string day = date.substr(monthPos + 1);

        switch (term) {
        case 'A':
            month += 6;
            if (month > 12) {
                year++;
                month -= 12;
            }
            break;
        case 'B':
            year++;
            break;
        case 'C':
            year += 2;
            break;
        case 'D':
            year += 3;
            break;
        }

        string temp = to_string(year) + '-' + (month > 10 ? "" : "0") +
            to_string(month) + '-'  + day;
        this->termDate = temp;
        this->key = year * 10000 + month * 100 + stoi(day);
    }

};
