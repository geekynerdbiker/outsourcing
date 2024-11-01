#include "game.h"

using namespace std;


void Game::read_file(string filename)
{
    ifstream ifs(filename);
    if (!ifs)
    {
        cerr << "Error: file open failed" << endl;
        exit(1);
    }
    
    ifs >> problem_id;

    if (problem_id == 0) {
        problem_specification = "";
    }
    else{
        ifs >> problem_specification;
    }

    cout << "problem_id: [" << problem_id << "]" << endl;
    cout << "problem_specification: [" << problem_specification << "]" << endl;

    // TODO: CREATE CHESSBOARD
    string width, height;

    ifs >> height >> width;
    board = new ChessBoard(stoi(width), stoi(height));


    vector<string> lines;
    string line;

    while (ifs >> line) {
        lines.push_back(line);
    }

    for (int i = 0; i < lines.size(); ++i) {
        for (int j = 0; j < lines[i].size(); ++j) {
            char piece_symbol = lines[i][j];
            if (piece_symbol != '.') {
                string color = (isupper(piece_symbol)) ? "White" : "Black";
                string type;
                switch (tolower(piece_symbol)) {
                case 'k': type = "King"; break;
                case 'q': type = "Queen"; break;
                case 'r': type = "Rook"; break;
                case 'b': type = "Bishop"; break;
                case 'n': type = "Knight"; break;
                case 'p': type = "Pawn"; break;
                default:
                    cerr << "Error: Unknown piece symbol encountered" << endl;
                    exit(1);
                }
                ChessPiece* piece = create_piece(color, type, i, j);
                board->place_piece(piece, i, j);

                if (color == "Black")
                    board->add_black_piece(piece);
                else
                    board->add_white_piece(piece);
            }
        }
    }
}

void Game::open_output_file(string filename)
{
    ofs.open(filename);
    if (!ofs)
    {
        cerr << "Error: file open failed" << endl;
        exit(1);
    }
}

void Game::solve()
{
    switch (problem_id)
    {
    case 0:
        solve_print_board();
        break;
    case 1:
        solve_print_possible_moves();
        break;
    case 2:
        solve_check();
        break;
    case 3:
        solve_checkmate();
        break;
    case 4:
        solve_checkmate_in_one_move();
        break;
    default:
        cout << "Invalid problem_id" << endl;
        break;
    }
    return;
}

void Game::solve_print_board()
{
    ofs << *board;
}

void Game::solve_print_possible_moves()
{
    // TODO
    int height = board->get_height();
    int width = board->get_width();

    ChessPiece* piece = (*board)[problem_specification];
    vector<tuple<MoveType, Direction, int>> possible_moves = piece->get_possible_moves();
    vector<vector<char>> moveMarkers(height, vector<char>(width, '.'));

    moveMarkers[piece->get_x()][piece->get_y()] = problem_specification[0];

    Direction curr;
    bool can_move_more = true;

    for (const auto& move : possible_moves) {
        if (!can_move_more && curr == get<1>(move))
            continue;

        int distance = get<2>(move);
        int directionX = direction_to_pair[get<1>(move)].first;
        int directionY = direction_to_pair[get<1>(move)].second;

        int moveX = piece->get_y();
        int moveY = piece->get_x();

        moveX += directionX * distance;
        moveY += directionY * distance;

        if (moveX >= 0 && moveX < width && moveY >= 0 && moveY < height) {
            if (board->get_tiles()[moveY][moveX] != nullptr) {
                if (piece->get_color() != board->get_tiles()[moveY][moveX]->get_color())
                    moveMarkers[moveY][moveX] = 'x';
                can_move_more = false;
                curr = get<1>(move);
            }
            else {
                moveMarkers[moveY][moveX] = 'o';
            }
        }
    }

    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            ofs << moveMarkers[r][c];
        }
        ofs << endl;
    }
}

int Game::solve_check()
{
    // TODO
    // EXAMPLE: "Black king is in check"
    //          "White king is not in check"
    int height = board->get_height();
    int width = board->get_width();

    set<ChessPiece*> pieces;
    string color = problem_specification;

    if (color == "w")
        pieces = board->get_black_pieces();
    else
        pieces = board->get_white_pieces();

    for (const auto& piece : pieces) {
        vector<tuple<MoveType, Direction, int>> possible_moves = piece->get_possible_moves();
        vector<vector<char>> moveMarkers(height, vector<char>(width, '.'));

        moveMarkers[piece->get_x()][piece->get_y()] = problem_specification[0];

        Direction curr;
        bool can_move_more = true;

        for (const auto& move : possible_moves) {
            if (!can_move_more && curr == get<1>(move))
                continue;

            int distance = get<2>(move);
            int directionX = direction_to_pair[get<1>(move)].first;
            int directionY = direction_to_pair[get<1>(move)].second;

            int moveX = piece->get_y();
            int moveY = piece->get_x();

            moveX += directionX * distance;
            moveY += directionY * distance;

            if (moveX >= 0 && moveX < width && moveY >= 0 && moveY < height) {
                if (board->get_tiles()[moveY][moveX] != nullptr) {
                    if (piece->get_color() != board->get_tiles()[moveY][moveX]->get_color())
                        moveMarkers[moveY][moveX] = 'x';
                    can_move_more = false;
                    curr = get<1>(move);
                }
                else {
                    moveMarkers[moveY][moveX] = 'o';
                }
            }
        }

        for (int r = 0; r < height; ++r) {
            for (int c = 0; c < width; ++c) {
                if (moveMarkers[r][c] == 'x' && board->get_tiles()[r][c]->get_type() == "King") {
                    if (color == "b")
                        ofs << "Black king is in check" << endl;
                    else
                        ofs << "White king is in check" << endl;
                    return 0;
                }
            }
        }
    }

    if (color == "b")
        ofs << "Black king is not in check" << endl;
    else
        ofs << "White king is not in check" << endl;
    return 0;
}

int Game::solve_checkmate()
{
    // TODO 
    // EXAMPLE: "Black king is checkmated"
    //          "White king is not checkmated"
    int height = board->get_height();
    int width = board->get_width();

    set<ChessPiece*> pieces;
    ChessPiece* king = nullptr;
    string color = problem_specification;
    vector<vector<char>> moveMarkers(height, vector<char>(width, '.'));
    vector<tuple<MoveType, Direction, int>> possible_king_moves;

    if (color == "w") {
        pieces = board->get_black_pieces();
        for (int r = 0; r < height; ++r)
            for (int c = 0; c < width; ++c) {
                if (board->get_tiles()[r][c] != nullptr && board->get_tiles()[r][c]->get_color() == "White" && board->get_tiles()[r][c]->get_type() == "King") {
                    king = board->get_tiles()[r][c];
                    break;
                }

            }
    }
    else {
        pieces = board->get_white_pieces();
        for (int r = 0; r < height; ++r)
            for (int c = 0; c < width; ++c) {
                if (board->get_tiles()[r][c] != nullptr && board->get_tiles()[r][c]->get_color() == "Black" && board->get_tiles()[r][c]->get_type() == "King") {
                    king = board->get_tiles()[r][c];
                    break;
                }

            }
    }

    possible_king_moves = king->get_possible_moves();

    Direction curr;
    bool can_move_more = true;

    for (const auto& move : possible_king_moves) {
        if (!can_move_more && curr == get<1>(move))
            continue;

        int distance = get<2>(move);
        int directionX = direction_to_pair[get<1>(move)].first;
        int directionY = direction_to_pair[get<1>(move)].second;

        int moveX = king->get_y();
        int moveY = king->get_x();

        moveX += directionX * distance;
        moveY += directionY * distance;

        if (moveX >= 0 && moveX < width && moveY >= 0 && moveY < height) {
            if (board->get_tiles()[moveY][moveX] != nullptr) {
                if (king->get_color() != board->get_tiles()[moveY][moveX]->get_color())
                    moveMarkers[moveY][moveX] = 'o';
                can_move_more = false;
                curr = get<1>(move);
            }
            else {
                moveMarkers[moveY][moveX] = 'o';
            }
        }
    }

    for (const auto& piece : pieces) {
        vector<tuple<MoveType, Direction, int>> possible_moves = piece->get_possible_moves();

        Direction curr;
        bool can_move_more = true;

        for (const auto& move : possible_moves) {
            if (!can_move_more && curr == get<1>(move))
                continue;

            int distance = get<2>(move);
            int directionX = direction_to_pair[get<1>(move)].first;
            int directionY = direction_to_pair[get<1>(move)].second;

            int moveX = piece->get_y();
            int moveY = piece->get_x();

            moveX += directionX * distance;
            moveY += directionY * distance;

            if (moveX >= 0 && moveX < width && moveY >= 0 && moveY < height) {
                if (board->get_tiles()[moveY][moveX] != nullptr) {
                    moveMarkers[moveY][moveX] = 'x';
                    can_move_more = false;
                    curr = get<1>(move);
                }
                else {
                    moveMarkers[moveY][moveX] = 'x';
                }
            }
        }
    }
        
    bool is_checkmated = true;

    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            if (moveMarkers[r][c] == 'o') {
                if (color == "b")
                    ofs << "Black king is not checkmated" << endl;
                else
                    ofs << "White king is not checkmated" << endl;
                return 0;
            }

        }
    }

    if (color == "b")
        ofs << "Black king is checkmated" << endl;
    else
        ofs << "White king is checkmated" << endl;
    return 0;
}

int Game::solve_checkmate_in_one_move()
{
    // TODO
    // EXAMPLE: "Black king is checkmated in one move"
    //          "White king is not checkmated in one move"
    int height = board->get_height();
    int width = board->get_width();

    set<ChessPiece*> pieces;
    string color = problem_specification;
        
    ChessBoard board2(*board);

    if (color == "w")
        pieces = board2.get_black_pieces();
    else
        pieces = board2.get_white_pieces();

    for (const auto& piece : pieces) {
        int original_x = piece->get_y();
        int original_y = piece->get_x();

        vector<tuple<MoveType, Direction, int>> possible_moves = piece->get_possible_moves();

        Direction curr = UP;
        bool can_move_more = true;

        for (const auto& move : possible_moves) {
            bool can_make_checkmate = true;
            ChessBoard temp_board(*board);
            if (!can_move_more && curr == get<1>(move))
                continue;

            int distance = get<2>(move);
            int directionX = direction_to_pair[get<1>(move)].first;
            int directionY = direction_to_pair[get<1>(move)].second;

            int moveX = piece->get_y();
            int moveY = piece->get_x();

            temp_board.get_tiles()[moveY][moveX] = nullptr;
            if (color == "w")
                temp_board.remove_black_piece(piece);
            else
                temp_board.remove_white_piece(piece);


            moveX += directionX * distance;
            moveY += directionY * distance;

            if (moveX >= 0 && moveX < width && moveY >= 0 && moveY < height) {
                piece->set_x(moveY);
                piece->set_y(moveX);

                temp_board.place_piece(piece, moveY, moveX);
                if (color == "w")
                    temp_board.add_black_piece(piece);
                else
                    temp_board.add_white_piece(piece);

                set<ChessPiece*> pieces2;
                ChessPiece* king = nullptr;
                vector<vector<char>> moveMarkers(height, vector<char>(width, '.'));
                vector<tuple<MoveType, Direction, int>> possible_king_moves;

                if (color == "b") {
                    pieces2 = temp_board.get_black_pieces();
                    for (const auto& p : pieces2) {
                        if (p->get_type() == "King") {
                            king = p;
                            break;
                        }
                    }
                    pieces2 = temp_board.get_white_pieces();
                }
                else {
                    pieces2 = temp_board.get_white_pieces();
                    for (const auto& p : pieces2) {
                        if (p->get_type() == "King") {
                            king = p;
                            break;
                        }
                    }
                    pieces2 = temp_board.get_black_pieces();
                }

                possible_king_moves = king->get_possible_moves();

                Direction curr2;
                bool can_move_more2 = true;

                for (const auto& move2 : possible_king_moves) {
                    if (!can_move_more2 && curr2 == get<1>(move2))
                        continue;

                    int distance2 = get<2>(move2);
                    int directionX2 = direction_to_pair[get<1>(move2)].first;
                    int directionY2 = direction_to_pair[get<1>(move2)].second;

                    int moveX2 = king->get_y();
                    int moveY2 = king->get_x();

                    moveX2 += directionX2 * distance2;
                    moveY2 += directionY2 * distance2;

                    if (moveX2 >= 0 && moveX2 < width && moveY2 >= 0 && moveY2 < height) {
                        if (temp_board.get_tiles()[moveY2][moveX2] != nullptr) {
                            if (king->get_color() != temp_board.get_tiles()[moveY2][moveX2]->get_color())
                                moveMarkers[moveY2][moveX2] = 'o';
                            can_move_more2 = false;
                            curr2 = get<1>(move2);
                        }
                        else {
                            moveMarkers[moveY2][moveX2] = 'o';
                        }
                    }
                }

                for (const auto& piece : pieces2) {
                    vector<tuple<MoveType, Direction, int>> possible_moves2 = piece->get_possible_moves();

                    Direction curr2;
                    bool can_move_more2 = true;

                    for (const auto& move2 : possible_moves2) {
                        if (!can_move_more2 && curr2 == get<1>(move2))
                            continue;

                        int distance2 = get<2>(move2);
                        int directionX2 = direction_to_pair[get<1>(move2)].first;
                        int directionY2 = direction_to_pair[get<1>(move2)].second;

                        int moveX2 = piece->get_y();
                        int moveY2 = piece->get_x();

                        moveX2 += directionX2 * distance2;
                        moveY2 += directionY2 * distance2;

                        if (moveX2 >= 0 && moveX2 < width && moveY2 >= 0 && moveY2 < height) {
                            if (temp_board.get_tiles()[moveY2][moveX2] != nullptr) {
                                moveMarkers[moveY2][moveX2] = 'x';
                                can_move_more2 = false;
                                curr2 = get<1>(move2);
                            }
                            else {
                                moveMarkers[moveY2][moveX2] = 'x';
                            }
                        }
                    }
                }

                for (int r = 0; r < height; ++r) {
                    for (int c = 0; c < width; ++c) {
                        if (moveMarkers[r][c] == 'o') {
                            can_make_checkmate = false;
                        }
                    }
                }

                if (!can_make_checkmate) {
                    piece->set_x(original_y);
                    piece->set_y(original_x);
                    continue;
                }
                else {
                    if (color == "b") {
                        ofs << "Black king is checkmated in one move" << endl;
                        return 0;
                    }
                    else {
                        ofs << "White king is checkmated in one move" << endl;
                        return 0;
                    }
                }

                
            }
        }
    }

    if (color == "b")
        ofs << "Black king is not checkmated in one move" << endl;
    else
        ofs << "White king is not checkmated in one move" << endl;
    return 0;
}

