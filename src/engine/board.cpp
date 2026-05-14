//
// Created by peter on 2026. 05. 02..
//

#include <iostream>
#include <vector>
#include "engine.h"



Position::Position(const int x, const int y) : x(x), y(y) {}

void Position::print() const {
    std::cout << x << " " << y << std::endl;
}

bool Position::upgrade(const std::string& color, const std::string& name) {
    if (color == "white" && name == "pawn" && y == 8) return true;
    if (color == "black" && name == "pawn" && y == 0) return true;
    return false;
}

bool Position::inside() {
    if (x >= 0 && x <= 8 && y >= 0 && y <= 8) return true;
    return false;
}



Moves::Moves(const std::vector<Position>& moves, const std::vector<Position>& captures, const std::vector<std::vector<Position>> moves_sections,std::vector<int> captures_section_mask) : moves(moves), captures(captures), moves_sections(moves_sections), captures_section_mask(captures_section_mask) {}


Player::Player(const std::string& name, const std::string color) :  name(name), color(color) {}


void Player::init_pieces() {

    int y = 1;
    if (color == "white") {
        y = 1;




        pieces.push_back(Piece("Rook", Position(0,0),color));
        pieces.push_back(Piece("Knight", Position(1,0),color));
        pieces.push_back(Piece("Bishop", Position(2,0),color));
        pieces.push_back(Piece("King", Position(4,0),color));
        pieces.push_back(Piece("Queen", Position(3,0),color));


        pieces.push_back(Piece("Bishop", Position(5,0),color));
        pieces.push_back(Piece("Knight", Position(6,0),color));
        pieces.push_back(Piece("Rook", Position(7,0),color));

        for (int i = 0; i < 8; i++) {
            //pieces_pawns.push_back(Piece(color, Position(i,y),color));
            pieces.push_back(Piece("Pawn", Position(i,y),color));
        }
    }
    else if (color == "black") {
        y = 6;
        pieces.push_back(Piece("King", Position(4,7),color));
        pieces.push_back(Piece("Queen", Position(5,7),color));

        pieces.push_back(Piece("Rook", Position(0,7),color));
        pieces.push_back(Piece("Knight", Position(1,7),color));
        pieces.push_back(Piece("Bishop", Position(3,7),color));

        pieces.push_back(Piece("Rook", Position(8,7),color));
        pieces.push_back(Piece("Knight", Position(7,7),color));
        pieces.push_back(Piece("Bishop", Position(6,7),color));

        for (int i = 0; i < 8; i++) {
            //pieces_pawns.push_back(Piece("Pawn", Position(i,y),color));
            pieces.push_back(Piece("Pawn", Position(i,y),color));
        }
    }
    std::cout << "Adding pawns" << std::endl;
}


bool Player::apply_move(Board board,const std::string &piece_name, const Position curr_pos, const Position next_pos, Player& other_player) {
    //cehck for check. If it was already check return false
    for (auto &p : pieces) {
        if (p.name == piece_name && check_postion(p.position,curr_pos)) {//TODO and position is hte same
            for (auto valid_move : p.moves_history.back().moves) {
                if (check_postion(next_pos,valid_move)) {
                    //save prev pos
                    Position prev_position = Position(p.position.x, p.position.y);
                    p.set_position(next_pos);
                    if (check(board,p) && piece_name == "King") {
                        p.set_position(prev_position);
                        continue;
                    }
                    //check for check
                    //if check invalidate and revert
                    p.moved = true;
                    return true;
                }
            }for (auto valid_move : p.moves_history.back().captures) {
                if (check_postion(next_pos,valid_move)) {
                    Position prev_position = Position(p.position.x, p.position.y);
                    p.set_position(next_pos);
                    if (check(board,p) && piece_name == "King") {
                        p.set_position(prev_position);
                        continue;
                    }
                    p.set_position(next_pos);
                    other_player.remove_piece(valid_move);
                    p.moved = true;
                    return true;
                }
            }

        }
    }
    return false;
}


void Player::remove_piece(const Position pos) {
    //auto& piece = pieces;

    std::erase_if(pieces, [&](const auto& p) {
        return check_postion(p.position, pos);
    });
}

void Board::remove_piece(std::string color, const Position pos) {
    int index = color == "white" ? 1 : 0;

    auto& pieces = players[index].pieces;

    std::erase_if(pieces, [&](const auto& p) {
        return check_postion(p.position, pos);
    });

}

//Piece::Piece(const std::string& name, const Position position, const std::string color) : position(position), name(name), color(color) {}

Piece::Piece(const std::string& name, const Position position, const std::string color)
    : name(name), position(position), color(color)
{
    // Assign move function based on piece name
    if      (name == "Rook")   moves_generation = rook_moves;
    else if (name == "Knight") moves_generation = knight_moves;
    else if (name == "Bishop") moves_generation = bishop_moves;
    else if (name == "Queen")  moves_generation = queen_moves;
    else if (name == "King")   moves_generation = king_moves;
    else                       moves_generation = pawn_moves; // fallback for pawns
}

void Piece::print_position(){}
Position Piece::get_position() const { return position; }
//std::vector<std::vector<Position>> get_valid_moves() const {}

Moves Piece::move(const Board& board)  {
    Moves move = moves_generation(board, *this);
    moves_history.push_back(move);
    return move;
}

void Piece::set_position(const Position& pos) { position.x=pos.x; position.y=pos.y; }






void Board::print() const {}


void Board::initialize() {
    players.push_back(Player("Player 1" , "white"));
    players.push_back(Player("Player 2","black"));

    for ( auto& player : players) {
        player.init_pieces();
    }
}



