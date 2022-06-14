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
		void login(string id, string pw){
		    // Your Code Here ...
		};

		// command 2
		void studentinfo(){
		    // Your Code Here ...
		};
		
		// command 3
		void scorerank(){
		    // Your Code Here ...
		};
		
		// command 4
		void scorestatistic(){
		    // Your Code Here ...
		};
		
		// command 5
		void alldata(){
		    // Your Code Here ...
		};
		
		// command 6
		void modifyinfo(){
		    // Your Code Here ...
		};
		
		// command 7
		void addstudent(){
		    // Your Code Here ...
		};
		
		// command 9
		void logout(){
		    // Your Code Here ...
		};
		// you can implement additional function
		
};	
#endif