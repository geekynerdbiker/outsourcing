#include "chessboard.h"

using namespace std;


void ChessBoard::initialize_board()
{
    // TODO: implement initialize_board
    tiles = new ChessPiece * *[height];
    for (int i = 0; i < height; ++i)
    {
        tiles[i] = new ChessPiece * [width];
        for (int j = 0; j < width; ++j)
        {
            tiles[i][j] = nullptr;
        }
    }
}

ostream& operator<<(ostream& os, const ChessBoard& board)
{
    // TODO: implement operator<<
    for (int i = 0; i < board.height; ++i)
    {
        for (int j = 0; j < board.width; ++j)
        {
            if (board.tiles[i][j] != nullptr)
            {
                if (board.tiles[i][j]->get_color() == "White")
                    os << piece_to_char[board.tiles[i][j]->get_type()];
                else
                    os << (char)(piece_to_char[board.tiles[i][j]->get_type()] + 32);
            }
            else
            {
                os << ".";
            }
        }
        os << endl;
    }
    return os;
}

ChessPiece* ChessBoard::operator[](string s)
{
    // TODO: implement operator[]

    string type = char_to_piece[toupper(s[0])];
    int column = s[1] - 'a';
    int row = height - (s[2] - '0');

    if (row >= 0 && row < height && column >= 0 && column < width && tiles[row][column]->get_type() == type)
    {
        return tiles[row][column];
    }
    else
    {
        return nullptr;
    }
}

ChessBoard& ChessBoard::operator=(const ChessBoard& other)
{
    // TODO: implement operator=
    if (this != &other)
    {
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                delete tiles[i][j];
            }
            delete[] tiles[i];
        }
        delete[] tiles;

        width = other.width;
        height = other.height;

        tiles = new ChessPiece * *[height];
        for (int i = 0; i < height; ++i)
        {
            tiles[i] = new ChessPiece * [width];
            for (int j = 0; j < width; ++j)
            {
                if (other.tiles[i][j] != nullptr)
                {
                    tiles[i][j] = other.tiles[i][j]->clone();
                }
                else
                {
                    tiles[i][j] = nullptr;
                }
            }
        }
    }
    return *this;
}
ChessBoard::ChessBoard(const ChessBoard& other)
{
    // TODO: implement copy constructor
    width = other.width;
    height = other.height;

    tiles = new ChessPiece * *[height];
    for (int i = 0; i < height; ++i)
    {
        tiles[i] = new ChessPiece * [width];
        for (int j = 0; j < width; ++j)
        {
            if (other.tiles[i][j] != nullptr)
            {
                tiles[i][j] = other.tiles[i][j]->clone();
            }
            else
            {
                tiles[i][j] = nullptr;
            }
        }
    }

    for (auto piece : other.white_pieces)
    {
        white_pieces.insert(piece->clone());
    }

    for (auto piece : other.black_pieces)
    {
        black_pieces.insert(piece->clone());
    }
}

// NOTE: YOU CAN ADD MORE FUNCTIONS HERE
void ChessBoard::place_piece(ChessPiece* piece, int x, int y)
{
    if (tiles[x][y] != nullptr) {
        tiles[x][y] = nullptr;
    }

    tiles[x][y] = piece;
}

void ChessBoard::add_black_piece(ChessPiece* piece) {
    black_pieces.insert(piece);
}

void ChessBoard::add_white_piece(ChessPiece* piece) {
    white_pieces.insert(piece);
}

void ChessBoard::remove_black_piece(ChessPiece* piece) {
    auto it = black_pieces.find(piece);
    if (it != black_pieces.end()) {
        black_pieces.erase(it);
    }
}
void ChessBoard::remove_white_piece(ChessPiece* piece) {
    auto it = white_pieces.find(piece);
    if (it != white_pieces.end()) {
        white_pieces.erase(it);
    }
}