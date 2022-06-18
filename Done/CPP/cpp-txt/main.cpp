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
    bool isAdmin = false;
    
    cout << "1. Login" << endl;
    cout << "2. Student info" << endl;
    cout << "3. Score Rank" << endl;
    cout << "4. Score statistic" << endl;
    cout << "9. Logout" << endl;
    cout << "0. Terminate" << endl;
    
    while (1) {
        if (isAdmin) {
            cout << "[Admin Command]" << endl;
            cout << "5. All data" << endl;
            cout << "6. Modify info" << endl;
            cout << "7. Add student" << endl;
        }
        
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
                if (isLoggedIn && id == Grade.admin())
                    isAdmin = true;
                else isAdmin = false;
            }
        } else if (cmd == 2) {
            if (!isLoggedIn)
                cout << "Please login first." << endl;
            else
                Grade.studentinfo();
        } else if (cmd == 3) {
            if (!isLoggedIn)
                cout << "Please login first." << endl;
            else
                Grade.scorerank();
        } else if (cmd == 4) {
            Grade.scorestatistic();
        } else if (cmd == 5) {
            if (!isAdmin)
                cout << "You do not have authority." << endl;
            else {
                Grade.alldata();
            }
        } else if (cmd == 6) {
            if (!isAdmin)
                cout << "You do not have authority." << endl;
            else {
                Grade.modifyinfo();
            }
        } else if (cmd == 7) {
            if (!isAdmin)
                cout << "You do not have authority." << endl;
            else {
                Grade.addstudent();
            }
        } else if (cmd == 9) {
            if (isLoggedIn) {
                isLoggedIn = false;
                isAdmin = false;
                cout << "Logout complete" << endl;
            } else
                cout << "You are not login." << endl;
            
        } else if (cmd == 0) {
            return 0;
        } else {
            cout << "Wrong Command." << endl;
        }
    }
}
