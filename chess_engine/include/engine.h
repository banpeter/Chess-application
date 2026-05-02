//
// Created by peter on 2026. 05. 02..
//

#ifndef CHESS_ENGINE_ENGINE_H
#define CHESS_ENGINE_ENGINE_H
#include <string>
#include <vector>


class Position {
public:
    int x, y;

    Position(const int x, const int y);
    void print() const;
    bool upgrade(const std::string& color, const std::string& name);
    bool inside();
};

class Moves {
public:
    //moves in one direction, is it check ->King ahs possible move outise of those, otehr pices canhas valide move with the moves in one direction
    std::vector<Position> moves;
    std::vector<Position> captures;
    std::vector<std::vector<Position>> moves_sections;
    std::vector<int> captures_section_mask;
    bool check_mate = false;
    Moves(const std::vector<Position>& moves, const std::vector<Position>& captures, const std::vector<std::vector<Position>> moves_sections,std::vector<int> captures_section_mask);

};

class Board;
class Piece;





using MoveFunction = Moves(*)(const Board&, const Piece&);
class Piece {
public:
    Position position;
    const std::string name;
    const std::string color;
    MoveFunction moves_generation;
    bool moved = false;
    std::vector<Moves> moves_history;

    Piece(const std::string& name, const Position position, const std::string color);
    void print_position();
    Position get_position() const;
    Moves move(const Board& board);
    void set_position(const Position& pos);

};








class Player {
public:
    std::string name;
    std::string color;
    std::vector<Piece> pieces_pawns;
    std::vector<Piece> pieces;
    std::vector<Moves> moves;
    Player(const std::string& name, const std::string color);
    void init_pieces();
};



class Board {

public:
    std::vector<std::vector<int>> board;
    std::vector<std::vector<int>> free_spaces;
    std::vector<Player> players;

    const int min_x = 0;
    const int min_y = 0;
    const int max_x = 8;
    const int max_y = 8;
    const int number_of_players = 2;

    void print() const;


    void initialize() ;
};

//Moves
Moves rook_moves(const Board& board, const Piece& chosen_piece);
Moves bishop_moves(const Board& board, const Piece& chosen_piece);
Moves knight_moves(const Board& board, const Piece& chosen_piece);
Moves pawn_moves(const Board& board, const Piece& chosen_piece);
Moves queen_moves(const Board& board, const Piece& chosen_piece);
Moves king_moves(const Board& board, const Piece& chosen_piece);



//helpers
bool check_postion(const Position p1, const Position p2);
bool check_move(const Board& board, const Position current_pos);
bool validate(Position current_position, Position next_position,Board board);
std::vector<Position> intersection(const std::vector<Position>& moves1, const std::vector<Position> moves2);


//minmax
int value(std::string name);
int evaluate(const Board& board,std::string color);

#endif //CHESS_ENGINE_ENGINE_H