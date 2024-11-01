#include <iostream>
#include <sstream>

using namespace std;

char fx[100];
int value[100];
int result, idx = 0;

void expr() {
    for (int i = 0; i < idx; i++) {
        switch (fx[i]) {
            case '+':
                result += value[i];
                break;
            
            case '*':
                result *= value[i];
                break;
            
            case '-':
                result -= value[i];
                break;
            
            case '/':
                result /= value[i];
                break;
            
            default:
                break;
        }
    }
    cout << result << endl;
}

void doCommand(char command) {
    switch (command) {
        case 's':
            idx = 0;
            cin >> result;
            break;
            
        case 'n':
            expr();
            break;
            
        case '+':
        case '*':
        case '-':
        case '/':
            fx[idx] = command;
            cin >> value[idx++];
            break;
            
        default:
            break;
    }
}


int main(int argc, const char * argv[]) {
    char command;
    
    while (cin >> command)
        doCommand(command);
 
    return 0;
}

