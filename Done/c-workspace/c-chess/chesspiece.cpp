#include "chesspiece.h"

using namespace std;


ChessPiece::ChessPiece(string color, string type, int x, int y, int flag)
{
    this->color = color;
    this->type = type;
    this->x = x;
    this->y = y;
    this->flag = flag;
}

ostream& operator<<(ostream& os, const ChessPiece& piece)
{
    char c;
    c = piece_to_char[piece.type];
    if (piece.color == "Black")
    {
        c = tolower(c);
    }
    os << c;
    return os;
}

ChessPiece::ChessPiece(const ChessPiece& other)
{
    this->color = other.color;
    this->type = other.type;
    this->x = other.x;
    this->y = other.y;
    this->flag = other.flag;
}

ChessPiece* create_piece(string color, string type, int x, int y, int flag)
{
    // TODO : implement create_piece
    if (type == "King")
        return new King(color, x, y, flag);
    if (type == "Queen")
        return new Queen(color, x, y, flag);
    if (type == "Rook")
        return new Rook(color, x, y, flag);
    if (type == "Bishop")
        return new Bishop(color, x, y, flag);
    if (type == "Knight")
        return new Knight(color, x, y, flag);
    if (type == "Pawn")
        return new Pawn(color, x, y, flag);
    return nullptr;
}

// NOTE: YOU CAN ADD OTHER FUNCTIONS HERE

vector<tuple<MoveType, Direction, int>> King::get_possible_moves()
{
    return {
         {MoveType::MOVE, UP, 1},
         {MoveType::MOVE, DOWN, 1},
         {MoveType::MOVE, LEFT, 1},
         {MoveType::MOVE, RIGHT, 1},
         {MoveType::MOVE, UP_LEFT, 1},
         {MoveType::MOVE, UP_RIGHT, 1},
         {MoveType::MOVE, DOWN_LEFT, 1},
         {MoveType::MOVE, DOWN_RIGHT, 1}
    };
}

vector<tuple<MoveType, Direction, int>> Queen::get_possible_moves()
{
    vector<tuple<MoveType, Direction, int>> moves;
    for (int i = 1; i <= 8; ++i)
        moves.push_back({ MoveType::MOVE, UP, i });
    for (int i = 1; i <= 8; ++i)
        moves.push_back({ MoveType::MOVE, DOWN, i });
    for (int i = 1; i <= 8; ++i)
        moves.push_back({ MoveType::MOVE, LEFT, i });
    for (int i = 1; i <= 8; ++i)
        moves.push_back({ MoveType::MOVE, RIGHT, i });
    for (int i = 1; i <= 8; ++i)
        moves.push_back({ MoveType::MOVE, UP_LEFT, i });
    for (int i = 1; i <= 8; ++i)
        moves.push_back({ MoveType::MOVE, UP_RIGHT, i });
    for (int i = 1; i <= 8; ++i)
        moves.push_back({ MoveType::MOVE, DOWN_LEFT, i });
    for (int i = 1; i <= 8; ++i)
        moves.push_back({ MoveType::MOVE, DOWN_RIGHT, i });

    return moves;
}

vector<tuple<MoveType, Direction, int>> Rook::get_possible_moves()
{
    vector<tuple<MoveType, Direction, int>> moves;
    for (int i = 1; i <= 8; ++i)
        moves.push_back({ MoveType::MOVE, UP, i });
    for (int i = 1; i <= 8; ++i)
        moves.push_back({ MoveType::MOVE, DOWN, i });
    for (int i = 1; i <= 8; ++i)
        moves.push_back({ MoveType::MOVE, LEFT, i });
    for (int i = 1; i <= 8; ++i)
        moves.push_back({ MoveType::MOVE, RIGHT, i });

    return moves;
}

vector<tuple<MoveType, Direction, int>> Bishop::get_possible_moves()
{
    vector<tuple<MoveType, Direction, int>> moves;
    for (int i = 1; i <= 8; ++i)
        moves.push_back({ MoveType::MOVE, UP_LEFT, i });
    for (int i = 1; i <= 8; ++i)
        moves.push_back({ MoveType::MOVE, UP_RIGHT, i });
    for (int i = 1; i <= 8; ++i)
        moves.push_back({ MoveType::MOVE, DOWN_LEFT, i });
    for (int i = 1; i <= 8; ++i)
        moves.push_back({ MoveType::MOVE, DOWN_RIGHT, i });
    
    return moves;
}

vector<tuple<MoveType, Direction, int>> Knight::get_possible_moves()
{
    return {
        {MoveType::MOVE, UP_UP_LEFT, 1},
        {MoveType::MOVE, UP_UP_RIGHT, 1},
        {MoveType::MOVE, DOWN_DOWN_LEFT, 1},
        {MoveType::MOVE, DOWN_DOWN_RIGHT, 1},
        {MoveType::MOVE, LEFT_LEFT_UP, 1},
        {MoveType::MOVE, LEFT_LEFT_DOWN, 1},
        {MoveType::MOVE, RIGHT_RIGHT_UP, 1},
        {MoveType::MOVE, RIGHT_RIGHT_DOWN, 1}
    };
}

vector<tuple<MoveType, Direction, int>> Pawn::get_possible_moves()
{
    vector<tuple<MoveType, Direction, int>> moves = {
        {MoveType::MOVE, UP, 1}
    };
    if (flag == 0)
    {
        moves.push_back({ MoveType::MOVE, UP, 2 });
    }

    moves.push_back({ MoveType::ATTACK, UP_LEFT, 1 });
    moves.push_back({ MoveType::ATTACK, UP_RIGHT, 1 });
    return moves;
}