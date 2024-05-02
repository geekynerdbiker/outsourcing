// Student ID Your Name
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

char sudoku[9][9] = {0};
void print(char arr[9][9]);
bool solved = false;

// you can implement additional function

bool isValidSudoku() {
    // Your Code Here ...
    for (int i = 0; i < 9; i++) {
        bool sudokuRowChecker[10] = {false};
        
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] - 48 == 0) continue;
            if (!sudokuRowChecker[sudoku[i][j] - 48])
                sudokuRowChecker[sudoku[i][j] - 48] = true;
            else return false;
        }
    }
    
    for (int i = 0; i < 9; i++) {
        bool sudokuColChecker[10] = {false};
        
        for (int j = 0; j < 9; j++) {
            if (sudoku[j][i] - 48 == 0) continue;
            if (!sudokuColChecker[sudoku[j][i] - 48])
                sudokuColChecker[sudoku[j][i] - 48] = true;
            else return false;
        }
    }
    
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            bool sudokuBoxChecker[10] = {false};

            for (int k = i; k < i + 3; k++)
                for (int l = j; l < j + 3; l++) {
                    if (sudoku[k][l] - 48 == 0) continue;
                    if (!sudokuBoxChecker[sudoku[k][l] - 48])
                        sudokuBoxChecker[sudoku[k][l] - 48] = true;
                    else return false;
                }
        }
    }
    return true;
}

bool solveSudoku(int i, int j) {
    // Your Code Here ...
    if (i > 8) {
        solved = true;
        return true;
    }
    
    if (sudoku[i][j] != '0') {
        if (j < 8)
            solveSudoku(i, j+1);
        else
            solveSudoku(i+1, 0);
    } else {
        char blank = '1';
        for (int k = 0; k < 9; k++) {
            sudoku[i][j] = blank;
            if (isValidSudoku()) {
                cout << endl;
                if (j < 8)
                    solveSudoku(i, j+1);
                else
                    solveSudoku(i+1, 0);
            }
            if (solved) return true;
            sudoku[i][j] = '0';
            blank += 1;
            
        }
        
    }
    return true;
}

int main(int argc, char** argv) {
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
