#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include "Cube.h"

using namespace std;

int main(void) {
    fstream fs;
    fs.open("WordBook.txt", ios::in);
    
    Cube cube;
    cube.initCube();
    
    while (!fs.eof()) {
        int x, y, z;
        char name[50] = {'\0', };
        
        fs >> z >> y >> x >> name;
        cube.insert(z, y, x, name);
        
    }
    
    fs.close();
    
    int command = 0;
    while (1) {
        int x = 0, y = 0, z = 0;
        char name[50] = {'\0', };
        
        cout << "Enter Any Command (1: Insert, 2: remove, 3: Find, 4: Print, 5: Print_All, 6: Turn, 7: Exchange, 8: Exit) : ";
        cin >> command;
        
        switch (command) {
            case 1:
                cin >> z >> y >> x >> name;
                cube.insert(z, y, x, name);
                break;
                
            case 2:
                cin >> z >> y >> x >> name;
                cube.remove(z, y, x, name);
                break;
                
            case 3:
                cin >> name;
                cube.find(name);
                break;
                
            case 4:
                cin >> z >> y >> x;
                cube.print(z, y, x);
                break;
                
            case 5:
                cube.printAll();
                break;
                
            case 6:
                cin >> z >> y >> x;
                cube.turn(z, y, x);
                cube.printAll();
                break;
                
            case 7:
                int x1, y1, z1, x2, y2, z2;
                cin >> z1 >> y1 >> x1 >> z2 >> y2 >> x2;
                cube.exchange(z1, y1, x1, z2, y2, x2);
                break;
                
            case 8:
                break;
                
            default:
                break;
        }
    }
    return 0;
}
