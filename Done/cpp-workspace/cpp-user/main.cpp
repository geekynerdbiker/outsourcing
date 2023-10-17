#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

class Account {
public:
    string name;
    string date;
    int balance;
    
};

class User {
public:
    string username;
    string password;
    vector<Account> accounts;
    
    int failed = 0;
    
    User(string username, string password) {
        this->username = username;
        this->password = password;
    }
};

bool validUsername(string username) {
    for (int i = 0; i < username.length(); i++) {
        if ('a' <= username[i] && username[i] <= 'z')
            continue;
        else if ('A' <= username[i] && username[i] <= 'Z')
            continue;
        else if ('0' <= username[i] && username[i] <= '9')
            continue;
        else
            return false;
    }
    return true;
}

bool existUsername(vector<User> users, string username) {
    for (int i = 0; i < users.size(); i++)
        if (!users[0].username.compare(username))
            return true;
    return false;
}

int validPassword(string password) {
    int count = 0;
    
    for (int i = 0; i < password.length(); i++) {
        if ('a' <= password[i] && password[i] <= 'z')
            continue;
        else if ('A' <= password[i] && password[i] <= 'Z')
            continue;
        else if ('0' <= password[i] && password[i] <= '9')
            continue;
        else if ('!' == password[i]) {
            count++;
            continue;
        } else if ('@' == password[i]) {
            count++;
            continue;
        } else if ('#' == password[i]) {
            count++;
            continue;
        } else if ('$' == password[i]) {
            count++;
            continue;
        } else if ('%' == password[i]) {
            count++;
            continue;
        } else if ('^' == password[i]) {
            count++;
            continue;
        } else if ('&' == password[i]) {
            count++;
            continue;
        } else if ('*' == password[i]) {
            count++;
            continue;
        } else
            return 0;
    }
    return count;
}

int findUsername(vector<User> users, string username) {
    for (int i = 0; i < users.size(); i++)
        if (!users[0].username.compare(username))
            return i;
    return -1;
}


bool checkPassword(vector<User> users, string username, string password) {
    for (int i = 0; i < users.size(); i++)
        if (!users[0].username.compare(username))
            if (!users[0].password.compare(password))
                return true;
    return false;
}

int main() {
    
    /**
     * File stream objects
     * Please do not change input and output file path.
     */
    ifstream f_in("input.txt");     // input file stream
    ofstream f_out("output.txt");   // output file stream
    
    /* Check the files are open */
    if (!f_in.is_open() || !f_out.is_open()) {
        cerr << "Error occured while opening files." << endl;
        return 1;
    }
    
    /* Implement your code */
    vector<User> users;
    string currentUsername;
    
    string l;
    vector<string> lines;
    while (getline(f_in, l)) {
        char separator = ' ';
        istringstream iss(l);
        string str_buf;
        
        vector<string> line;
        while (getline(iss, str_buf, separator)) {
            line.push_back(str_buf);
        }
        
        if (!line[0].compare("cu")) {
            string username = line[1];
            string password = line[2];
            
            if (username.length() > 20) {
                f_out << "Request failed: The username should not be longer than 20." << endl;
                continue;
            } if (!validUsername(username)) {
                f_out << "Request failed: The username must consist of numbers of English only." << endl;
                continue;
            } if (existUsername(users, username)) {
                f_out << "Request failed: The name is already taken." << endl;
                continue;
            } if (8 > password.length() || password.length() > 20) {
                f_out << "Request failed: The password should be in a range from 8 to 20." << endl;
                continue;
            } if (!validPassword(password)) {
                f_out << "Request failed: The username must consist of numbers, English, and only {!, @, #, $, %, ^, &, *}." << endl;
                continue;
            } if (validPassword(password) == 0) {
                f_out << "Request failed: The username must consist of numbers, English, and at least one of the special symbols {!, @, #, $, %, ^, &, *}." << endl;
                continue;
            }
            
            User user(username, password);
            users.push_back(user);
            f_out << "A user named \'" << username << "\' is created." << endl;
        } else if (!line[0].compare("li")) {
            string username = line[1];
            string password = line[2];
            
            if (currentUsername.length() > 0) {
                f_out << "Request failed: You are already login. (current username: \'" << username << "\')"<< endl;
                continue;
            } if (!existUsername(users, username)) {
                f_out << "Request failed: There is no user named \'" << username << "\'." << endl;
                continue;
            } if (users[findUsername(users, username)].failed == 5) {
                f_out << "Request failed: The user named \'" << username << "\' is inactivated." << endl;
                continue;
            } if (!checkPassword(users, username, password)) {
                if (++users[findUsername(users, username)].failed == 5)
                    f_out << "Request failed: The password is incorrect. [You failed: " << users[findUsername(users, username)].failed << ", The user named  \'" << username << "\' is inactivated." << endl;
                else
                    f_out << "Request failed: The password is incorrect. [You failed: " << users[findUsername(users, username)].failed << " \'" << username << "\'." << endl;
                continue;
            }
            currentUsername = username;
            f_out << "A user named \'" << username << "\' is logged in." << endl;
        } else if (!line[0].compare("lo")) {
            if (currentUsername.length() == 0) {
                f_out << "Request failed: You are not logged in."<< endl;
                continue;
            }
            currentUsername = "";
            f_out << "You are successfully logged out." << endl;
        } else if (!line[0].compare("cda")) {
            string accountName = line[1];
            string date = line[2];
        } else if (!line[0].compare("d")) {
            
        } else if (!line[0].compare("w")) {
            
        } else if (!line[0].compare("r")) {
            
        } else if (!line[0].compare("abo")) {
            
        } else if (!line[0].compare("ota")) {
            
        } else if (!line[0].compare("cja")) {
            
        }
    }
    
    //////////////////////////////////////////////////////
    f_in.close();
    f_out.close();
    
    return 0;
}

/* Implement your own functions */
