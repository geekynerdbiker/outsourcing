#include <iostream>
#include <ctime>
#include <array>

using namespace std;

const int boardLen{ 5 };
int bombProb{ 10 };
enum class Status { CONTINUE, WON, LOST };

Status gameStep(array <array <int, boardLen>, boardLen>&, const array<int, 2>&);
bool isWon(array <array <int, boardLen>, boardLen>& board);
int getBomb(array <array <int, boardLen>, boardLen>& board, int row, int col);
void printBoard(const array <array <int, boardLen>, boardLen>&);
void printAllBomb(const array <array <int, boardLen>, boardLen>&);

int main()
{
    // TO-DO
    // You must implement main function!
    // You can use below template codes, but you have to design the overall algorithm and implement the C++ code yourself.
    array <array <int, boardLen>, boardLen> board;
    array <int, 2> move;
    
    srand(static_cast<unsigned int>(time(0)));

    for (int i{ 0 }; i < boardLen; i++) {
        for (int j{ 0 }; j < boardLen; j++) {
            if (rand() % 100 < bombProb) board[i][j] = -2;
            else board[i][j] = -1;
        }
    }
    Status status = Status::CONTINUE;
    
    while (status == Status::CONTINUE) {
        printBoard(board);
        
        cout << "Enter the row number of your next move: ";
        cin >> move[0];
        
        cout << "Enter the column number of your next move: ";
        cin >> move[1];
        
        cout << endl;
        
        status = gameStep(board, move);
    }
}

Status gameStep(array <array <int, boardLen>, boardLen>& board, const array<int, 2>& move) {
    // TO-DO
    // You must implement gameStep function!
    
    if (board[move[0]][move[1]] == -1)
        board[move[0]][move[1]] = getBomb(board, move[0], move[1]);
    else if (board[move[0]][move[1]] == -2) {
        printAllBomb(board);
        cout << "BOOM! You lost." << endl;
        return Status::LOST;
    } else
        cout << "Already opened." << endl;
    
    if (isWon(board)){
        printAllBomb(board);
        cout << "Congratulations! You won." << endl;
        return Status::WON;
    }
    return Status::CONTINUE;
}

bool isWon(array <array <int, boardLen>, boardLen>& board) {
    for (int i{ 0 }; i < boardLen; i++)
        for (int j{ 0 }; j < boardLen; j++)
            if (board[i][j] == -1)
                return false;
    return true;
}

int getBomb(array <array <int, boardLen>, boardLen>& board, int row, int col) {
    int dir[][2] = { {1,1}, {1,0}, {1,-1}, {0,1}, {0,-1}, {-1,1}, {-1,0}, {-1,-1} };
    int bombs = 0;
    
    for (int i = 0; i < 8; i++) {
        int x = row+dir[i][0];
        int y = col+dir[i][1];
        
        if (x < 0 || y < 0 || x >= boardLen || y >= boardLen)
            continue;
        if (board[x][y] == -2)
            bombs++;
    }
    return bombs;
}

void printAllBomb(const array <array <int, boardLen>, boardLen>& board) {
    // TO-DO
    // You must implement printAllBomb function!
    cout << "    ";
    for (int i{ 0 }; i < boardLen; i++) {
        cout << i << " ";
    }
    cout << "\n   ";
    for (int i{ 0 }; i < boardLen; i++) {
        cout << "__";
    }
    cout << endl;
    for (int i{ 0 }; i < boardLen; i++) {
        cout << i << " | ";
        for (int j{ 0 }; j < boardLen; j++) {
            if (board[i][j] == -2) {
                cout << "B ";
            }
            else if (board[i][j] == -1) {
                cout << ". ";
            }
            else {
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void printBoard(const array <array <int, boardLen>, boardLen>& board) {
    // Caution!
    // Do not edit the printBoard function!
    
    cout << "    ";
    for (int i{ 0 }; i < boardLen; i++) {
        cout << i << " ";
    }
    cout << "\n   ";
    for (int i{ 0 }; i < boardLen; i++) {
        cout << "__";
    }
    cout << endl;
    for (int i{ 0 }; i < boardLen; i++) {
        cout << i << " | ";
        for (int j{ 0 }; j < boardLen; j++) {
            if (board[i][j] == -2) {
                cout << ". ";
            }
            else if (board[i][j] == -1) {
                cout << ". ";
            }
            else {
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}
