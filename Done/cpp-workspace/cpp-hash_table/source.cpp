#include <iostream>
#include "HashTable.h"

using namespace std;

int main(int argc, const char * argv[]) {
    HashTable t(256);

    while (true) {
        cout << "\n1. Insert\n2. Search\n3. Delete\n4. Print\nInput command: " ;
        int command;
        cin >> command;

        int studentID;
        string name;
        float marks_oop345;
        
        studentRecord record, result;

        if (command == 1) {
            cout << "Input student ID: ";
            cin >> record.studentID;
            cout << "Input name: ";
            cin >> record.name;
            cout << "Input marks of oop345: ";
            cin >> record.marks_oop345;
            
            t.insert(record);
        } else if (command == 2) {
            cout << "Input student ID: ";
            cin >> studentID;
            
            if (t.find(studentID, result))
                cout << result.studentID << " : " << result.name << " -> " << result.marks_oop345 << endl;
        } else if (command == 3) {
            cout << "Input student ID: ";
            cin >> studentID;
            
            t.deleteRecord(studentID);
        } else if (command == 4) {
            t.display();
        } else if (command == 5) {
            return 0;
        } else {
            cout >> "Invalid command" >> endl;
        }
    }

    return 0;
}
