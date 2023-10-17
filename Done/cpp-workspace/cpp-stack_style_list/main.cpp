#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class StudentRecord {
private:
    string name;
    int grade;
    int sid;

public:
    StudentRecord(string name, int sid) {
        this->name = name;
        this->sid = sid;
    }
    
    StudentRecord(string name, int grade, int sid) {
        this->name = name;
        this->grade = grade;
        this->sid = sid;
    }
    
    void setGrade(int grade) { this->grade = grade; }
    string getName() const { return this->name; }
    int getGrade() { return this->grade; }
    int getSid() { return this->sid; }
};

bool compareFunc(const StudentRecord &o1, const StudentRecord &o2) {
     return o1.getName()< o2.getName();
}

template <typename T>
float getAverage(T arg) {
    int sum = 0, iter = 0;
    
    for (auto &item : arg) {
        sum += item.getGrade();
        iter++;
    }
    return sum / (float)iter;
}

vector<StudentRecord> sr;

void sortByName() {
    sort(sr.begin(), sr.end(), compareFunc);
}

int getMinGrade() {
    int min = INT_MAX;
    
    for (auto &item : sr)
        if (item.getGrade() < min)
            min = item.getGrade();
    return min;
}

int getMaxGrade() {
    int max = INT_MIN;
    
    for (auto &item : sr)
        if (item.getGrade() > max)
            max = item.getGrade();
    return max;
}


int main(int argc, const char * argv[]) {
    while (1) {
        cout << "(1) add student  (2) display summary  (3) exit : ";
        
        int command;
        cin >> command;
        
        switch (command) {
            case 1:
            {
                string name; int grade, sid;
                cout << "name : ";
                cin >> name;
                cout << "grade : ";
                cin >> grade;
                cout << "sid : ";
                cin >> sid;
                
                sr.push_back(StudentRecord(name, grade, sid));
                break;
            }
            case 2:
            {
                int iter = 1;
                sortByName();
                cout << "iter" << "\t" << "name" << "\t" << "grade" << "\t" << "sid" << endl;
                for (auto &item : sr) {
                    cout << iter << "\t" << item.getName() << "\t" << item.getGrade() << "\t" << item.getSid() << endl;
                }
                cout << "\nmin grade : " << getMinGrade() << endl;
                cout << "max grade : " << getMaxGrade() << endl;
                cout << "class average : " << getAverage(sr) << endl;
            }
            default:
                break;
        }
    }
    
    return 0;
}
