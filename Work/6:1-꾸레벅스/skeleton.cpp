// Student ID Your Name
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

char sudoku[9][9] = {0};
void print(char arr[9][9]);

// you can implement additional function

bool isValidSudoku(){
    // Your Code Here ...
}

bool solveSudoku(int i, int j){ 
    // Your Code Here ...
}

int main(int argc, char** argv){
    // 1. read input file and make sudoku board
    string intput_filename(argv[1]);
    ifstream inFile(intput_filename);
    string line;
    int idx=0;
    while (getline(inFile, line)){
        strcpy(sudoku[idx],line.c_str());
        idx++;
    }
    inFile.close();
    // print(sudoku);


    // 2. task 1: determine valid sudoku
    bool valid = isValidSudoku(); // you should implement this function by your own style.


    // 3. task 2: fill in Sudoku
    if (valid){
        solveSudoku(0, 0); // you should implement this function by your own style.
    }
    // print(sudoku);


    // 4. make output file - DON'T EDIT
    string output_filename(argv[2]);
    ofstream outFile(output_filename);

    if (!valid){
        string message = "This is invalid sudoku\n";
        outFile << message.c_str();
    }
    else{
        for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){
                char tmp = sudoku[i][j];
                outFile << tmp;
            }
            outFile<<endl;
        }
    }
    outFile.close();
    return 0;
}

void print(char arr[9][9]){ // you can use this function freely for your convenience.
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++)
            cout << arr[i][j] << " ";
        cout << endl;
    }
}
