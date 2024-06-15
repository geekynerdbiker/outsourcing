#pragma once
/*
 * board.h
 */
#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cctype>

#include "utils.h"
#include "chesspiece.h"

using namespace std;


class ChessBoard
{
public:
    void initialize_board();
    
    ChessBoard(int width, int height): width(width), height(height) { initialize_board(); }

    ChessBoard& operator=(const ChessBoard& other);
    
    friend ostream& operator<<(ostream& os, const ChessBoard& board);
    ChessPiece* operator[](string s);

    ChessBoard(const ChessBoard& other);

    // NOTE: YOU CAN ADD MORE MEMBER FUNCTIONS HERE
    ChessPiece*** get_tiles() const { return tiles; }
    void place_piece(ChessPiece* piece, int x, int y);
    void add_black_piece(ChessPiece* piece);
    void add_white_piece(ChessPiece* piece);
    void remove_black_piece(ChessPiece* piece);
    void remove_white_piece(ChessPiece* piece);
    set<ChessPiece*> get_black_pieces() const { return black_pieces; }
    set<ChessPiece*> get_white_pieces() const { return white_pieces; }
    int get_width() const { return width; }
    int get_height() const { return height; }

private: 
    int width, height;
    ChessPiece*** tiles;
    set<ChessPiece*> white_pieces;
    set<ChessPiece*> black_pieces;

    // NOTE: YOU CAN ADD MORE MEMBER VARIABLESS HERE

};

// NOTE: YOU CAN ADD MORE FUNCTIONS HERE

#endif /* CHESSBOARD_H_ */