#ifndef SetSolver_h
#define SetSolver_h

#include <string>
#include <iostream>
#include <vector>

using std::vector;
using std::string;
//You can add another .h class to help you create a data structure of your choosing.

class SetSolver {
private:
    int boardSize = 9;
    vector<vector<string>> board;
    vector<vector<vector<string>>> posibilities;
public:
    void PopulateBoard(vector<string> skeletonBoard) {
        // implement your code here
        for (int i = 0; i < boardSize; i++) {
            vector<string> v;
            vector<vector<string>> p;
            bool op = true;
            for (int j = 0; j < skeletonBoard[i].length(); j++) {
                string s;
                if (skeletonBoard[i][j] == '*') {
                    s = "99";
                    p.push_back({"1", "2", "3", "4", "5", "6", "7", "8", "9"});
                } else if (skeletonBoard[i][j] == '-') {
                    op = false;
                    continue;
                }
                else {
                    if (op) {
                        s = std::to_string(skeletonBoard[i][j] - '0');
                        p.push_back({s});
                    }
                    else {
                        s = std::to_string(int(skeletonBoard[i][j] - '0') * -1);
                        p.push_back({s});
                        op = true;
                    }
                }
                v.push_back(s);
            }
            board.push_back(v);
            posibilities.push_back(p);
        }
    }
    
    int ReturnValue(size_t row, size_t col) {
        // implement your code here
        //return the right value
        return stoi(board[row][col]);
    }
    
    void RemovePosibilities() {
        // implement your code here
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (posibilities[i][j].size() > 1) {
                    for (int k = 0; k < boardSize; k++) {
                        string s1 = board[i][k];
                        string s2 = board[k][j];
                        
                        if (s1[0] == '-')
                            s1 = board[i][k][1];
                        if (s2[0] == '-')
                            s2 = board[k][j][1];
                        
                        posibilities[i][j].erase(remove(posibilities[i][j].begin(), posibilities[i][j].end(), s1), posibilities[i][j].end());
                        posibilities[i][j].erase(remove(posibilities[i][j].begin(), posibilities[i][j].end(), s2), posibilities[i][j].end());
                        
                    }
                }
            }
        }
    }
    
    vector<int> ReturnPosibilities(int row, int col) {
        // implement your code here
        // return the correct values based on the requested square. vector<int> temp {1,2,3,4};
        vector<int> temp;
        
        for (int i = 0; i < posibilities[row][col].size(); i++)
            temp.push_back(stoi(posibilities[row][col][i]));
        return temp;
    }
    
    void NearlyThere(int row, int col, string direction) {
        // implement your code here
            
    }
    
    void Solve() {
        // implement your code here
        
    }
    
    // for test
    void printBoard() {
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                std::cout << board[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }
};
#endif /* SetSolver_h */
