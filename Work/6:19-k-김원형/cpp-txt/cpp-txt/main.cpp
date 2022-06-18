// Student ID Your Name
#include"project.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>

using namespace std;


int main(){
    // read input file
    Project Grade;
    Grade.readfile();
    
    // Your Code Here ...
    bool isLoggedIn = false;
    cout << "1. Login" << endl;
    cout << "2. Student info" << endl;
    cout << "3. Score Rank" << endl;
    cout << "4. Score statistic" << endl;
    cout << "9. Logout" << endl;
    cout << "0. Terminate" << endl;
    
    while (1) {
        int cmd;
        
        cout << "Select the command: ";
        cin >> cmd;
        
        if (cmd == 1) {
            if (isLoggedIn)
                cout << "You've already logged in." << endl;
            else {
                cin.ignore(100,'\n');
                string id, pw;
                cout << "Student name: ";
                getline(cin, id);
                cout << "Password: ";
                getline(cin, pw);
                
                isLoggedIn = Grade.login(id, pw);
            }
        } else if (cmd == 2) {
            if (!isLoggedIn)
                cout << "Please login first." << endl;
            else
                Grade.studentinfo();
        }
    }
}
