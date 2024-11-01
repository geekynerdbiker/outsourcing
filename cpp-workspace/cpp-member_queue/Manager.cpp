#include "Manager.h"

#define FIRST_CHARACTER 0
#define LOAD_ERROR 100
#define ADD_ERROR 200
#define QPOP_ERROR 300
#define SEARCH_ERROR 400
#define PRINT_ERROR 500
#define DELETE_ERROR 600

using namespace std;

// constructor
Manager::Manager() {
    
}

// disstructor
Manager::~Manager() {

}

// driver function
void Manager::run(const char* command) {
    // Open command & log file
    fcmd.open(command);
    flog.open("log.txt");
    if (!fcmd) {
        flog << "Fail to open command file" << endl;
        exit(-1);
    }

    // Run command
    
    // create instances
    NameBST* nameBST = new NameBST;
    TermsLIST* termsLSIT = new TermsLIST;
    MemberQueue* memberQueue = new MemberQueue;
    
    // read line
    string line;
    while (true) {
        fcmd >> line;
        
        // parse line by command cases.
        if (line == "LOAD")
            LOAD(memberQueue);
        else if (line == "QPOP")
            QPOP(termsLSIT, memberQueue, nameBST);
        else if (line.substr(0, line.find(' ')) == "ADD")
            ADD(memberQueue);
        else if (line.substr(0, line.find(' ')) == "SEARCH")
            SEARCH(nameBST);
        else if (line.substr(0, line.find(' ')) == "PRINT")
            PRINT(termsLSIT, nameBST);
        else if (line.substr(0, line.find(' ')) == "DELETE")
            DELETE(termsLSIT, nameBST);
        else if (line == "EXIT") {
            PrintSuccess("EXIT");
            break;
        }
        else {
            PrintErrorCode(1000);
            exit(-1);
        }
    }

    fcmd.close();
    flog.close();
    return;
}

// print success messege from parameter
void Manager::PrintSuccess(const char* command) {
    flog << "===== " << command << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl << endl;
}

// print error code from prameter
void Manager::PrintErrorCode(int errorCode) {
    flog << "===== ERROR =====" << endl;
    flog << errorCode << endl;
    flog << "===============" << endl << endl;
}

// inorder traverse printer
template<typename T>
void Manager::inorderPrint(T* t) {
    if (t == nullptr) return;

    inorderPrint(t->getLeft());
    flog << t->getName() << '/' << t->getAge() << '/' << t->getDate() << '/' << t->getTermDate() << '\n';
    inorderPrint(t->getRight());
}

// LOAD
void Manager::LOAD(MemberQueue* memberQueue) {
    ifstream fin;
    fin.open("data.txt");

    if (!fin.is_open() || !memberQueue->empty()) {
        PrintErrorCode(LOAD_ERROR);
        fin.close();
        return;
    }
    
    string data = "";
    string name;
    string date;
    int age;
    char term;
    

    // check valid data
    getline(fin, data);
    if (data == "") {
        PrintErrorCode(LOAD_ERROR);
        fin.close();
        return;
    }
    
    flog << "===== LOAD =====\n";
    
    stringstream ss(data);
    ss >> name >> age >> date >> term;
    flog << name << '/' << age << '/' << date << '/' << term << '\n';
    MemberQueueNode* memberQueueNode = new MemberQueueNode(name, date, age, term);
    
    // push node if not full
    if (!memberQueue->full())
        memberQueue->push(memberQueueNode);
    
    // push data while queue is not full
    while (!memberQueue->full()) {
        data = "";
        getline(fin, data);
        
        if (data == "")
            break;
        
        stringstream ss(data);
        ss >> name >> age >> date >> term;
        flog << name << '/' << age << '/' << date << '/' << term << '\n';
        
        MemberQueueNode* memberQueueNode = new MemberQueueNode(name, date, age, term);
        memberQueue->push(memberQueueNode);
    }
    flog << "===============\n\n";

    fin.close();
}

// ADD
void Manager::ADD(MemberQueue* memberQueue) {
    string name;
    string date;
    int age;
    char term;
    fcmd >> name >> age >> date >> term;

    // check valid data
    if (!(term >= 'A' && term <= 'D') || age > 100) {
        PrintErrorCode(ADD_ERROR);
        return;
    }
    
    // push while queue is not full
    MemberQueueNode* memberQueueNode = new MemberQueueNode(name, date, age, term);
    if (!memberQueue->full()) {
        memberQueue->push(memberQueueNode);
        flog << "===== ADD =====\n";
        flog << name << '/' << age << '/' << date << '/' << term << '\n';
        flog << "===============\n\n";
    } else {
        flog << "Memeber Queue over\n";
    }
    return;

}

// QPOP
void Manager::QPOP(TermsLIST* termLIST, MemberQueue* memberQueue, NameBST* nameBST) {
    // check queue is empty
    if (memberQueue->empty()) {
        PrintErrorCode(QPOP_ERROR);
        return;
    } else {
        while (!memberQueue->empty()) {
            MemberQueueNode* memberQueueNode = memberQueue->front();
            termLIST->insert(memberQueueNode, nameBST);
            memberQueue->pop();
        }
        PrintSuccess("QPOP");
    }
}

// SEARCH
void Manager::SEARCH(NameBST* nameBST) {
    string name;
    fcmd >> name;

    NameBSTNode* nameBSTNode = nameBST->search(name);
    // check node is valid
    if (!nameBSTNode) {
        PrintErrorCode(SEARCH_ERROR);
        return;
    } else {
        flog << "===== SEARCH =====\n";
        flog << name << '/' << nameBSTNode->getAge() << '/' << nameBSTNode->getDate() << '/' << nameBSTNode->getTermDate() << '\n';
        flog << "===============\n\n";
    }
}



// PRINT
void Manager::PRINT(TermsLIST* termsLIST, NameBST* nameBST) {
    string input;
    fcmd >> input;

    // check token
    if (input != "NAME") {
        char c = input[FIRST_CHARACTER];
        TermsBST* termsBST = termsLIST->PrintTermsBST(c);

        // check node is valid
        if (!termsBST) {
            PrintErrorCode(PRINT_ERROR);
            return;
        } else {
            flog << "===== PRINT =====\n";
            flog << "Terms_BST " << c << '\n';
            inorderPrint(termsBST->getRoot());
            flog << "===============\n\n";
        }
    } else {
        // check node is valid
        if (!nameBST->getRoot()) {
            PrintErrorCode(PRINT_ERROR);
            return;
        } else {
            flog << "===== PRINT =====\n";
            flog << "Name_BST " << '\n';
            inorderPrint(nameBST->getRoot());
            flog << "===============\n\n";
        }
    }
}

// DELETE
void Manager::DELETE(TermsLIST* termsLIST, NameBST* nameBST) {
    // check node is valid
    if (!nameBST->getRoot()) {
        PrintErrorCode(DELETE_ERROR);
        return;
    }

    string input;
    string data;
    fcmd >> input >> data;

    // check token
    if (input == "DATE") {
        // check list is valid
        if (!termsLIST->getDelete()) {
            termsLIST->deleteDate(nameBST, data);
            PrintSuccess("DELETE");
        }
        else {
            PrintErrorCode(600);
            return;
        }
    } else {
        string date;
        NameBSTNode* nameBSTNode = nameBST->search(data);
        if (nameBSTNode) date = nameBSTNode->getTermDate();

        char term = nameBST->remove(data);
        // check node is valid
        if (!term) {
            PrintErrorCode(DELETE_ERROR);
            return;
        } else {
            termsLIST->deleteName(data, date, term);
            termsLIST->decrease();
            PrintSuccess("DELETE");
        }
    }
}
