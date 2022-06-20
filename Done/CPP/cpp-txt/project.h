#ifndef PROJECT_H
#define PROJECT_H
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
//All parts of codes are freely modifiable.
using namespace std;
struct Info{
    string idlist[20], pwlist[20];
    double HW1[20], HW2[20], PJ1[20], PJ2[20];
    int loginfail[20]; // login fail count (default: 0)
};

class Project
{
private:
    // you can add more member variable
    string userid;
    int userindex;
    Info info;
    int studentnum=11;
    const string adminid = "admin";
    const string adminpw = "unisteee";
public:
    // read input file. Each data is saved in structure Info.
    void readfile(){
        ifstream inFile("input.txt");
        string line;
        
        if(inFile.is_open()){
            for(int i=0; i<studentnum; i++){
                getline(inFile, line)>> info.idlist[i] >> info.pwlist[i] >> info.HW1[i] >> info.HW2[i] >> info.PJ1[i] >> info.PJ2[i];
            }
        }
        inFile.close();
        for(int i=0;i<studentnum;i++){
            info.loginfail[i]=0;
        }
    }
    
    // command 1
    bool login(string id, string pw) {
        // Your Code Here ...
        if (id == adminid && pw == adminpw) {
            cout << "Login Success." << endl;
            return true;
        }
        
        for (int i = 0; i < studentnum; i++) {
            if (info.idlist[i] == id) {
                if (info.loginfail[i] >= 3) {
                    cout << "Please contact administrator and reset your password." << endl;
                    return false;
                } if (info.pwlist[i] == pw) {
                    cout << "Login Success." << endl;
                    userid = id;
                    userindex = i;
                    info.loginfail[i] = 0;
                    return true;
                } else {
                    cout << "Login Fail." << endl;
                    return false;
                }
            }
        }
        cout << "Login Fail." << endl;
        return false;
    };
    
    // command 2
    void studentinfo() {
        // Your Code Here ...
        cout << "Name: " << info.idlist[userindex] << endl;
        cout << "Homework: " << info.HW1[userindex] << " " << info.HW2[userindex] << endl;
        cout << "Project: " << info.PJ1[userindex] << " " << info.PJ2[userindex] << endl;
        
    };
    
    // command 3
    void scorerank(){
        // Your Code Here ...
        int hw1 = 1, hw2 = 1, pj1 = 1, pj2 = 1;
        
        for (int i = 0; i < studentnum; i++) {
            if (i == userindex)
                continue;
            if (info.HW1[i] > info.HW1[userindex])
                hw1++;
            if (info.HW2[i] > info.HW2[userindex])
                hw2++;
            if (info.PJ1[i] > info.PJ1[userindex])
                pj1++;
            if (info.PJ2[i] > info.PJ2[userindex])
                pj2++;
            
        }
        cout << "Your rank is..." << endl;
        cout << "HW1: " << hw1 << endl;
        cout << "HW2: " << hw2 << endl;
        cout << "Project1: " << pj1 << endl;
        cout << "Project2: " << pj2 << endl;
        
    };
    
    // command 4
    void scorestatistic(){
        // Your Code Here ...
        double HW1[20], HW2[20], PJ1[20], PJ2[20];
        double avgHW1 = 0, avgHW2 = 0, avgPJ1 = 0, avgPJ2 = 0;
        double medHW1, medHW2, medPJ1, medPJ2;
        
        for (int i = 0; i < studentnum; i++) {
            HW1[i] = info.HW1[i];
            HW2[i] = info.HW2[i];
            PJ1[i] = info.PJ1[i];
            PJ2[i] = info.PJ2[i];
        }
        
        array_sort(HW1);
        array_sort(HW2);
        array_sort(PJ1);
        array_sort(PJ2);
        
        for (int i = 0; i < studentnum; i++) {
            avgHW1 += HW1[i];
            avgHW2 += HW2[i];
            avgPJ1 += PJ1[i];
            avgPJ2 += PJ2[i];
        }
        
        if (studentnum % 2 == 1) {
            medHW1 = HW1[studentnum/2];
            medHW2 = HW2[studentnum/2];
            medPJ1 = PJ1[studentnum/2];
            medPJ2 = PJ2[studentnum/2];
        } else {
            medHW1 = (HW1[studentnum/2] + HW1[studentnum/2-1]) / 2;
            medHW2 = (HW2[studentnum/2] + HW2[studentnum/2-1]) / 2;
            medPJ1 = (PJ1[studentnum/2] + PJ1[studentnum/2-1]) / 2;
            medPJ2 = (PJ2[studentnum/2] + PJ2[studentnum/2-1]) / 2;
        }
        
        cout << "Average scores and median scores are..." << endl;
        cout << "HW1: " << avgHW1/studentnum << ", " << medHW1 << endl;
        cout << "HW2: " << avgHW2/studentnum << ", " << medHW2 << endl;
        cout << "Project1: " << avgPJ1/studentnum << ", " << medPJ1 << endl;
        cout << "Project1: " << avgPJ2/studentnum << ", " << medPJ2 << endl;
    };
    
    // command 5
    void alldata(){
        // Your Code Here ...
        cout << "All data:" << endl;
        for (int i = 0; i < studentnum; i++) {
            cout << info.idlist[i] << ": ";
            cout << info.HW1[i] << " ";
            cout << info.HW2[i] << " ";
            cout << info.PJ1[i] << " ";
            cout << info.PJ2[i] << endl;
        }
    };
    
    // command 6
    void modifyinfo(){
        // Your Code Here ...
        string name, part;
        cin.ignore(100,'\n');
        
        cout << "Whose information are you going to modify?: ";
        getline(cin, name);
        cout << "What information are you going to modify?(password, HW1, HW2, PJ1, PJ2): ";
        getline(cin, part);
        
        int index = 0;
        for (int i = 0; i < studentnum; i++)
            if (info.idlist[i] == name) {
                index = i;
                break;
            }
        
        if (part == "password") {
            string password;
            
            cout << "Enter new password: ";
            getline(cin, password);
            
            bool lower = false, upper = false, number = false, punctuation = false;
            for (int i = 0; i < password.length(); i++) {
                if (password[i] >= 'a' && password[i] <= 'z')
                    lower = true;
                if (password[i] >= 'A' && password[i] <= 'Z')
                    upper = true;
                if (password[i] >= '0' && password[i] <= '9')
                    number = true;
                if (password[i] < 'a' && password[i] > 'z')
                    if (password[i] < 'A' && password[i] > 'Z')
                        if (password[i] < '0' && password[i] > '9')
                            punctuation = true;
                
            }
            
            if (lower && upper && number && punctuation) {
                info.pwlist[index] = password;
                cout << "Change complete." << endl;
            } else {
                cout << "Wrong password." << endl;
            }
        } else if (part == "HW1") {
            double score;
            
            cout << "Enter new score: ";
            cin >> score;
            
            if (score >= 0 && score <= 20) {
                info.HW1[index] = score;
                cout << "Change complete." << endl;
            } else
                cout << "Wrong Input." << endl;
        } else if (part == "HW2") {
            double score;
            
            cout << "Enter new score: ";
            cin >> score;
            
            if (score >= 0 && score <= 30) {
                info.HW2[index] = score;
                cout << "Change complete." << endl;
            } else
                cout << "Wrong Input." << endl;
        } else if (part == "PJ1") {
            double score;
            
            cout << "Enter new score: ";
            cin >> score;
            
            if (score >= 0 && score <= 100) {
                info.PJ1[index] = score;
                cout << "Change complete." << endl;
            } else
                cout << "Wrong Input." << endl;
        } else if (part == "PJ2") {
            double score;
            
            cout << "Enter new score: ";
            cin >> score;
            
            if (score >= 0 && score <= 100) {
                info.PJ2[index] = score;
                cout << "Change complete." << endl;
            } else
                cout << "Wrong Input." << endl;
        }
    };
    
    // command 7
    void addstudent(){
        // Your Code Here ...
        string name, password;
        double HW1, HW2, PJ1, PJ2;
        
        cin.ignore(100, '\n');
        
        cout << "Student name: ";
        getline(cin, name);
        
        cout << "Password: ";
        getline(cin, password);
        
        cout << "HW1 score: ";
        cin >> HW1;
        if (HW1 < 0 || HW1 > 20) {
            cout << "Wrong input." << endl;
            return;
        }
        
        cout << "HW2 score: ";
        cin >> HW2;
        if (HW2 < 0 || HW2 > 30) {
            cout << "Wrong input." << endl;
            return;
        }
        
        cout << "PJ1 score: ";
        cin >> PJ1;
        if (PJ1 < 0 || PJ1 > 100) {
            cout << "Wrong input." << endl;
            return;
        }
        
        cout << "PJ2 score: ";
        cin >> PJ2;
        if (PJ2 < 0 || PJ2 > 100) {
            cout << "Wrong input." << endl;
            return;
        }
        
        info.idlist[studentnum] = name;
        info.pwlist[studentnum] = password;
        
        info.HW1[studentnum] = HW1;
        info.HW2[studentnum] = HW2;
        info.PJ1[studentnum] = PJ1;
        info.PJ2[studentnum] = PJ2;
        info.loginfail[studentnum] = 0;
        
        studentnum++;
    };
    
    // command 9
    void logout(){
        // Your Code Here ...
    };
    // you can implement additional function
    
    void array_sort(double a[]){
        for (int i = 0; i < studentnum; i++) {
            double min = a[i];
            int index = i;
            for (int j = i+1; j < studentnum; j++) {
                if (min > a[j]) {
                    min = a[j];
                    index = j;
                }
            }
            swap(a[i], a[index]);
        }
    }
    
    string admin(){
        return adminid;
    }
};	
#endif
